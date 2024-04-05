#ifndef BATTERYMANAGER_H
#define BATTERYMANAGER_H

#include <QObject>

class BatteryManager : public QObject
{
    Q_OBJECT
public:
    explicit BatteryManager(QObject *parent = nullptr);
    void setDrainSpeed(int speed);

signals:
    void batteryPercentageChanged(int percentage);

public slots:
    void startBatterySimulation();

private:
    void drainBattery();
    int batteryPercentage = 100;
    int drainSpeed = 2;
};

#endif // BATTERYMANAGER_H
