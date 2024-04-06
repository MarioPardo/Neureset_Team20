#ifndef BATTERYMANAGER_H
#define BATTERYMANAGER_H

#include <QObject>

class BatteryManager : public QObject
{
    Q_OBJECT
public:
    explicit BatteryManager(QObject *parent = nullptr);
    void setDrainSpeed(int speed);
    void startBatterySimulation();

signals:
    void batteryPercentageChanged(int percentage);


private:
    void drainBattery();
    int batteryPercentage = 100;
    int drainSpeed = 1;
};

#endif // BATTERYMANAGER_H
