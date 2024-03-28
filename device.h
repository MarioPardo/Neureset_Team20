#ifndef DEVICE_H
#define DEVICE_H

#include "defs.h"

#include <string>
#include <QVector>
#include <QDateTime>
#include <QTimer>
#include <QObject>
#include "sensor.h"



class Device : public QObject
{
   Q_OBJECT
public:
    Device(QObject *parent = nullptr);
    ~Device();

    void Display(std::string);
    void SensorDisconnected(int sensor);

    void StartSession();
    void pause();
    void stop();
    void reset();

public slots:
    void run();

private:

    QVector<Sensor*> sensors;
    QVector<Sensor*> sensorQueue;
    int powerPercentage = 100;
    DEVICE_STATE state = READY;
    DEVICE_STATE prevState = state;
    QDateTime pausedTime;

    QTimer* runTimer;

    float firstBaseline = NULL;
    float secondBaseline = NULL;

    float CalculateBaseline();
    float calcDomFreq();



};

#endif // DEVICE_H
