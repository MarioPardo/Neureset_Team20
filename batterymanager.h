#ifndef BATTERYMANAGER_H
#define BATTERYMANAGER_H

#include <QObject>
#include "defs.h"

class BatteryManager : public QObject
{
    Q_OBJECT
public:
    explicit BatteryManager(QObject *parent = nullptr);
    void fastDrain(bool b);
    void startBatterySimulation();
signals:
    void batteryPercentageChanged(int percentage);


private:
    void drainBattery();
    int percentage = 100;
    int drainSpeed = DRAIN_RATE_SLOW;
};

#endif // BATTERYMANAGER_H
