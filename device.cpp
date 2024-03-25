#include "device.h"
#include <iostream>
#include <QThread>

Device::Device()
{
    std::cout << "Device Constructor" << std::endl;

    for(int i= 0; i < 21; i++) {
        Sensor* newSensor = new Sensor();
        sensors.append(newSensor);
    }
}


void Device::StartSession()
{
    //TODO make pseudo code for running session
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
    //TODO hook up to UI display
}


void Device::pause()
{
    //TODO implement waiting for unpause behaviour

    if(state == PAUSED)
    {
        Display("DEVICE UNPAUSED, RESUMING");
        QThread::sleep(1);
        Display("DEVICE UNPAUSED, RESUMING");
        state = prevState;
    }
    else
    {
        Display("DEVICE PAUSED");
        prevState = state;
        state = PAUSED;


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

