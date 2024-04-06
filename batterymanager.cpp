#include "batterymanager.h"
#include <iostream>
#include "batterymanager.h"
#include <QTimer>

BatteryManager::BatteryManager(QObject *parent) : QObject(parent)
{
    std::cout<<"Battery Manager CTOR"<<std::endl;
}

void BatteryManager::setDrainSpeed(int speed)
{
    drainSpeed = speed;
}

void BatteryManager::startBatterySimulation()
{
    // Create a QTimer to simulate battery drain
    QTimer *batteryTimer = new QTimer(this);
    connect(batteryTimer, &QTimer::timeout, this, &BatteryManager::drainBattery);
    batteryTimer->start(2000); // Start the timer to call drainBattery every 2 seconds
}

void BatteryManager::drainBattery()
{
    // Update battery percentage
    batteryPercentage -= drainSpeed;
    if (batteryPercentage < 0) {
        batteryPercentage = 0;
    }

    emit batteryPercentageChanged(batteryPercentage);

    std::cout<< "Batery Percentage at: " << batteryPercentage <<std::endl;

    if (batteryPercentage == 0) {
        // Stop battery simulation or take appropriate action
    }
}

