#include "device.h"
#include <iostream>
#include <QThread>
#include <QTimer>
#include "batterymanager.h"
#include <sstream>
#include "mainmenu.h"
#include "session.h"


Device::Device(QObject *parent, BatteryManager* batM, MainMenu* mainM, QPlainTextEdit* textEdit) : QObject(parent)
{
    std::cout << "Device Constructor" << std::endl;

    batteryManager = batM;
    mainMenu = mainM;
    displayArea = textEdit;



    for(int i= 0; i < 7; i++) {
        Sensor* newSensor = new Sensor(i, DESIRED_FREQUENCY_TYPE);
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
            stop();
            return;
        }
    }

    if(state == FIRST_OVERALL)
    {
        Display("Calculating first Baseline");
        firstBaseline = CalculateBaseline();

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
            Display("Finished round #: " + std::to_string(treatmentRound) + "!" );

            if(treatmentRound  == numRounds) //finished treatment, go to next step
            {
                treatmentRound = NULL;
                sensorQueue.clear();
                state = SECOND_OVERALL;
            }

            //not last round, prep for next round
            sensorQueue.clear();
            for(Sensor* s : sensors)
                sensorQueue.append(s);

            treatmentRound ++;

            return;
        }

        Sensor* sensor = sensorQueue.front();
        sensorQueue.erase(sensorQueue.begin());


        float domFreq = sensor->CalculateDominantFrequency();
        flashFrame(greenLED,"green");
        sensor->ApplyTreatment(domFreq,treatmentRound);

        return;
    }
    else if(state == SECOND_OVERALL)
    {
        Display("Calculating Second Baseline Baseline");
        secondBaseline = CalculateBaseline();

        EndSession();


        state = READY;
        return;
    }

}



float Device::CalculateBaseline()
{
    return 5.0f; //rand value for now
}

void Device::EndSession()
{
    if(mainMenu == nullptr)
    {
        cout << "null";
    }
    Display(" SESSION FINISHED");
    batteryManager->fastDrain(false);
    runTimer->stop();

    QDateTime dateTime = QDateTime::currentDateTime();
    Session *session = new Session(dateTime,firstBaseline,secondBaseline,0.00);
    mainMenu->addSession(session);

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

    std::string toOutput = setToString(disconnectedSensors);
    Display(" Disconnected Sensors: " + toOutput +  " ");
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

void Device::Display(std::string str)
{
    displayArea->clear();
    displayArea->setPlainText(QString::fromStdString(str));
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
    //quit ui and go back to main menu
}

void Device::reset()
{
    Display("RESETTING");
    //quit ui and go back to main menu
}


