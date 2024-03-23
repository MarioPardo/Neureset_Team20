#include "device.h"
#include <iostream>
#include <QThread>

Device::Device()
{
    std::cout << "Device Constructor" << std::endl;

}


void Device::StartSession()
{
    //TODO make pseudo code for running session
}

//takes in a bunch of frequencies from sensor to make calculation
float Device::calcDomFreq(std::vector<int>)
{
    float domFreq = 0.0;

    return domFreq;
}


void Device::SensorDisconnected(int sensor)\
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

