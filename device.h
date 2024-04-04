#ifndef DEVICE_H
#define DEVICE_H

#include "defs.h"
#include <string>
#include <QVector>
#include <QTime>
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
    int treatmentRound = NULL;
    int powerPercentage = 100;
    DEVICE_STATE state = READY;
    DEVICE_STATE prevState = state;
    QTime pausedTime;

    QTimer* runTimer;

    float firstBaseline = NULL;
    float secondBaseline = NULL;

    float CalculateBaseline();
    float calcDomFreq();

    void EndSession();

};

#endif // DEVICE_H
