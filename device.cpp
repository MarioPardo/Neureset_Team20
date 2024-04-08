#include "device.h"
#include <iostream>
#include <QThread>
#include <QTimer>
#include "batterymanager.h"

Device::Device(QObject *parent, BatteryManager* batM) : QObject(parent)
{
    std::cout << "Device Constructor" << std::endl;

    batteryManager = batM;

    for(int i= 0; i < 7; i++) {
        Sensor* newSensor = new Sensor(i, ALPHA);
        sensors.append(newSensor);
    }

}

Device::~Device()
{
    std::cout<< "Device DTOR" <<std::endl;
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

    std::cout << "STARTING SESSION" <<std::endl;
    
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
        if(pausedTime.msecsTo(QTime::currentTime()) >= 5000)
        {
            Display("DEVICE TIMED OUT");
            stop();
            return;
        }
    }

    if(state == FIRST_OVERALL)
    {
        std::cout << "Calculating first Baseline" <<std::endl;
        firstBaseline = CalculateBaseline();

        //finished calculating baseline, now prep for next step
        sensorQueue.clear();
        for(Sensor* s : sensors)
            sensorQueue.append(s)  ;


        state = APPLYING_TREATMENT;
        treatmentRound = 1;
        return;
    }
    else if(state == APPLYING_TREATMENT)
    {


        if(sensorQueue.isEmpty())
        {
            std::cout<<"Finished round #: "<< treatmentRound << std::endl;

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
        sensor->ApplyTreatment(domFreq,treatmentRound);

        return;
    }
    else if(state == SECOND_OVERALL)
    {
        std::cout << "Calculating Second Baseline Baseline" <<std::endl;
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
    std::cout<<" SESSION FINISHED" <<std::endl;
    batteryManager->fastDrain(false);
    runTimer->stop();
}


//takes in a bunch of frequencies from sensor to make calculation
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
        disconnectedSensors.erase(sensor);
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


void Device::Display(std::string str)
{
    std::cout << str << std::endl;
    //TODO hook up to UI display
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

