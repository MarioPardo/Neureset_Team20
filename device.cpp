#include "device.h"
#include <iostream>
#include <QThread>
#include <QTimer>
#include "batterymanager.h"
#include <sstream>
#include "mainmenu.h"
#include "datetimewindow.h"
#include "session.h"
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

Device::Device(QObject *parent, BatteryManager* batM, MainMenu* mainM, QPlainTextEdit* textEdit, ActiveSessionWindow* activesesh, QDateTime selectedDateTime) : QObject(parent)

{
    std::cout << "Device Constructor" << std::endl;

    batteryManager = batM;
    mainMenu = mainM;
    displayArea = textEdit;
    activeSessionWindow = activesesh;

    dtw = new datetimewindow;

    for(int i= 0; i < 7; i++) {
        Sensor* newSensor = new Sensor(i + 1, DESIRED_FREQUENCY_TYPE);
        sensors.append(newSensor);
    }
}

Device::~Device()
{
    std::cout<< "Device DTOR" <<std::endl;
}


Sensor* Device::getSensor(int index)
{
    return this->sensors.at(index);
}


void Device::setLEDLights(QFrame* green, QFrame* blue, QFrame* red)
{
    greenLED = green;
    blueLED = blue;
    redLED = red;
}

void Device::StartSession()
{

    if(state == PAUSED)
    {
        pause(); //will handle unpausing
        return;
    }

    if(!disconnectedSensors.empty())
        return;

    Display("STARTING SESSION");
    blueLED->setStyleSheet("background-color: blue;");
    batteryManager->fastDrain(true);
    runTimer = new QTimer(this);
    connect(runTimer, &QTimer::timeout, this, &Device::run);
    runTimer->start(1500);
    secondsRemaining = SESSION_LENGTH;


    state = FIRST_OVERALL;
}

void Device::run()
{
    if(state == READY)
        return;


    if(state == PAUSED)
    {
        if(pausedTime.msecsTo(QTime::currentTime()) >= pauseTimeout)
        {
            Display("DEVICE TIMED OUT");
            activeSessionWindow->on_stop_Btn_clicked();
        }

        return;
    }


    secondsRemaining--;
    activeSessionWindow->updateProgress(secondsRemaining);




    if(state == FIRST_OVERALL)
    {
        Display("Calculating first Baseline");
        firstBaseline = CalculateBaseline();
        qDebug() << "Initial baseline: " << QString::number(firstBaseline);

        //finished calculating baseline, now prep for next step
        sensorQueue.clear();
        for(Sensor* s : sensors)
            sensorQueue.append(s)  ;


        state = APPLYING_TREATMENT;
        treatmentRound = 1;
        Display("Starting Treatment");

        return;
    }

    else if(state == APPLYING_TREATMENT)
    {

        if(sensorQueue.isEmpty())
        {
            if(treatmentRound == numRounds) //finished treatment, go to next step
            {
                treatmentRound = NULL;
                sensorQueue.clear();
                state = SECOND_OVERALL;
                return;
            }
            sensorQueue.clear();
            for(Sensor* s : sensors) {
                sensorQueue.append(s);
            }
            treatmentRound++;
            return;
        }

         Display("Treatment Round: " + QString::number(treatmentRound));

        flashFrame(greenLED, "green");

        //creating a list of future objects because qtconcurrent run returns one of these when finished
        QList<QFuture<void>> futures;
        for(Sensor* sensor : sensorQueue) {
            QFuture<void> future = QtConcurrent::run([=]() {
                float domFreq = sensor->CalculateDominantFrequency();
                sensor->ApplyTreatment(domFreq, treatmentRound);
            });
            futures.append(future);
        }


        //wait for treatments on each electrode to be finished
        for(QFuture<void> f: futures) {
           f.waitForFinished();
        }

        Display("Finished round #: " + QString::number(treatmentRound) + "!" );
        sensorQueue.clear();
        state = ANALYZING;
        std::cout.flush();
        analyzedStart = QTime::currentTime();
    }

    else if(state == ANALYZING)
    {
        for(Sensor* s: sensors)
        {
            float newTargetFreq = s->generateNewFrequency();
            s->generateFrequenciesAndAmplitudes(newTargetFreq);
            s->generateVoltageGraphData();
            s->CalculateDominantFrequency();
        }
        Display("Analyzing");

        if(analyzedStart.msecsTo(QTime::currentTime()) >= pauseTimeout)
        {
            state = APPLYING_TREATMENT;
            pausedTime = QTime();
        }



    }

    else if(state == SECOND_OVERALL)
    {
        Display("Calculating Second Baseline");
        secondBaseline = CalculateBaseline();
        qDebug () << "New baseline frequency: " << secondBaseline;
        EndSession();

        return;
    }
}


float Device::CalculateBaseline()
{
    float totalDomFreq = 0.0;
    for(Sensor* s: sensors) {
        totalDomFreq += s->CalculateDominantFrequency();
    }
    return totalDomFreq / NUM_SENSORS;
}

void Device::EndSession()
{
    Display(" SESSION FINISHED");
    batteryManager->fastDrain(false);
    runTimer->stop();
    activeSessionWindow->updateProgress(0);
    secondsRemaining = SESSION_LENGTH;

    QDateTime dateTime = mainMenu->getSelectedDateTime(); //gets device's date and time

    Session *session = new Session(dateTime,firstBaseline,secondBaseline);
    mainMenu->addSession(session);

    reset();
}


float Device::calcDomFreq()
{
    float totalDomFreq = 0.0;
    for(Sensor* s: sensors) {
        totalDomFreq += s->CalculateDominantFrequency();
    }
    return totalDomFreq / sensors.size();
}


void Device::SensorDisconnected(int sensor)
{
    if(disconnectedSensors.find(sensor) != disconnectedSensors.end())
        disconnectedSensors.erase(sensor);  //if reconnecting already disconnected sensor
    else
        disconnectedSensors.insert(sensor);


    if(disconnectedSensors.empty())
    {
        pause(); //handles unpausing
        return;
    }
    else
    {
        if(state != PAUSED)
            pause();

    }

    QString toOutput = QString::fromStdString(setToString(disconnectedSensors));
    Display("Disconnected Sensors: " + toOutput +  " ");
    flashFrame(redLED, "red");
}

std::string Device::setToString(const std::set<int>& mySet) {
    std::stringstream ss;
    ss << "[";
    bool isFirst = true;
    for (int num : mySet) {
        if (!isFirst) {
            ss << ", ";
        }
        ss << num;
        isFirst = false;
    }
    ss << "]";
    return ss.str();
}


void Device::flashFrame(QFrame* frame, std::string color) {

    frame->setStyleSheet("background-color: " + QString::fromStdString(color) + ";");
    frame->update();
    QApplication::processEvents();
    QThread::msleep(200);
    frame->setStyleSheet("background-color: lightgrey;");
    frame->update();
    QApplication::processEvents();

}

void Device::Display(QString str)
{
    displayArea->clear();
    displayArea->setPlainText(str);
    displayArea->update();
    QApplication::processEvents();
}


void Device::pause()
{
    if(!runTimer)
    {
        Display(" NOTHING TO PAUSE!");
        return;
    }


    if(state == PAUSED)
    {
        if(!disconnectedSensors.empty())
            return;

        Display("DEVICE UNPAUSED, RESUMING");
        batteryManager->fastDrain(true);
        state = prevState;
        pausedTime = QTime();
    }
    else
    {
        Display("DEVICE PAUSED");
        batteryManager->fastDrain(false);
        prevState = state;
        state = PAUSED;
        pausedTime = QTime::currentTime();
        return;
    }

}

void Device::stop()
{
    Display("STOPPING SESSION");
    displayArea->update();
    QApplication::processEvents();

}

void Device::reset()
{

    treatmentRound = -1;
    state = READY;
    prevState = state;
    firstBaseline = -1;
    secondBaseline = -1;
    blueLED->setStyleSheet("background-color: lightgrey;");

    Display("READY FOR NEW SESSION");



}


