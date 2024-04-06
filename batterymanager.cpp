#include "batterymanager.h"
#include <iostream>
#include "defs.h"
#include <QTimer>
#include <QApplication>
#include <QMessageBox>

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
    batteryTimer->start(DRAIN_RATE_SECS * 1000); // Start the timer to call drainBattery every 2 seconds
}

void BatteryManager::drainBattery()
{
    // Update battery percentage
    percentage -= drainSpeed;
    if (percentage < 0) {
        percentage = 0;
    }

    emit batteryPercentageChanged(percentage);

}

