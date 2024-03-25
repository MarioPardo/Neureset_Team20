#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H
#include "sensor.h"

class SensorManager
{
public:
    SensorManager();
    float calculateAvgDomFreq();

private:
    QVector<Sensor*> sensors;
};

#endif // SENSORMANAGER_H
