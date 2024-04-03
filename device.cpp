#include "device.h"
#include <iostream>
#include <QThread>
#include <QTimer>

Device::Device(QObject *parent) : QObject(parent)
{
    std::cout << "Device Constructor" << std::endl;

    for(int i= 0; i < 21; i++) {
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

    std::cout << "STARTING SESSION" <<std::endl;

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
            stop();
        return;
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
        return;
    }
    else if(state == APPLYING_TREATMENT)
    {

         //TODO implement treatment rounds

        if(sensorQueue.isEmpty())
        {
            std::cout<<"Finished applying treatment" <<std::endl;
            //set up for next step

            return;
        }

        Sensor* sensor = sensorQueue.front();
        sensorQueue.erase(sensorQueue.begin());

        float domFreq = sensor->CalculateDominantFrequency();
        sensor->ApplyTreatment(domFreq,1);

        return;
    }
    else if(state == SECOND_OVERALL)
    {
        std::cout << "Calculating Second Baseline Baseline" <<std::endl;
        secondBaseline = CalculateBaseline();

        //finished treatment, now store it and set device to ready for new session

        std::cout<<" SESSION FINISHED" <<std::endl;
        runTimer->stop();


        state = READY;
        return;
    }

}

float Device::CalculateBaseline()
{
    return 5.0f; //rand value for now
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
    Display(" SENSOR " + std::to_string(sensor) + " DISCONNECTED \n ");

    pause();

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
        Display("DEVICE UNPAUSED, RESUMING");
        state = prevState;
    }
    else
    {
        Display("DEVICE PAUSED");
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

