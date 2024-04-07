#include "batterymanager.h"
#include <iostream>
#include <QTimer>
#include <QApplication>
#include <QMessageBox>

BatteryManager::BatteryManager(QObject *parent) : QObject(parent)
{
    std::cout<<"Battery Manager CTOR"<<std::endl;
}

void BatteryManager::fastDrain(bool b)
{
    drainSpeed = DRAIN_RATE_SLOW;

    if(b)
        drainSpeed = DRAIN_RATE_FAST;

}

void BatteryManager::startBatterySimulation()
{
    // Create a QTimer to simulate battery drain
    QTimer *batteryTimer = new QTimer(this);
    connect(batteryTimer, &QTimer::timeout, this, &BatteryManager::drainBattery);
    batteryTimer->start(2000); //every 2 secs
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

