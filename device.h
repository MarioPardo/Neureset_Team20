#ifndef DEVICE_H
#define DEVICE_H

#include "defs.h"
#include <string>
#include <QVector>
#include <set>
#include <QTime>
#include <QDateTime>
#include <QTimer>
#include <QObject>
#include <sstream>
#include "sensor.h"


class BatteryManager;
class MainMenu;
class Session;

class Device : public QObject
{
   Q_OBJECT
public:
   Device(QObject *parent = nullptr, BatteryManager* batM = nullptr, MainMenu* mainM = nullptr);
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

    MainMenu* mainMenu;
    BatteryManager* batteryManager;
    QVector<Sensor*> sensors;
    QVector<Sensor*> sensorQueue;
    std::set<int> disconnectedSensors;
    int treatmentRound = NULL;
    int powerPercentage = 100;
    DEVICE_STATE state = READY;
    DEVICE_STATE prevState = state;
    QTime pausedTime;
    int numRounds = 4;

    QTimer* runTimer;

    float firstBaseline = NULL;
    float secondBaseline = NULL;

    float CalculateBaseline();
    float calcDomFreq();

    std::string setToString(const std::set<int>& mySet);

    void EndSession();

};

#endif // DEVICE_H
