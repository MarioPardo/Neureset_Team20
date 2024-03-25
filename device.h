#ifndef DEVICE_H
#define DEVICE_H

#include "defs.h"

#include <string>
#include <QVector>
#include <QDateTime>
#include "sensor.h"


class Device
{
public:
    Device();

    void Display(std::string);

    void SensorDisconnected(int sensor);

private:

    //Sensor sensors[21];

    int powerPercentage = 100;
    DEVICE_STATE state = READY;
    DEVICE_STATE prevState = state;

    void pause();
    void stop();
    void reset();
    QVector<Sensor*> sensors;
    void StartSession();
    float calcDomFreq();
};

#endif // DEVICE_H
