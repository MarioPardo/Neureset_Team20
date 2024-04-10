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
#include <QPlainTextEdit>

class BatteryManager;
class MainMenu;
class Session;

class Device : public QObject
{
   Q_OBJECT
public:

   Device(QObject *parent = nullptr, BatteryManager* batM = nullptr, MainMenu* mainM = nullptr,QPlainTextEdit* textEdit = nullptr);

    ~Device();

    void Display(std::string);
    void SensorDisconnected(int sensor);

    void setLEDLights(QFrame* green, QFrame* blue, QFrame* red);

    void StartSession();
    void pause();
    void stop();
    void reset();
    Sensor* getSensor(int index);

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
    int pauseTimeout = 7000;

    QTimer* runTimer;
    QPlainTextEdit* displayArea;

    QFrame* greenLED;
    QFrame* blueLED;
    QFrame* redLED;

    void flashFrame(QFrame* frame, std::string color);


    float firstBaseline = NULL;
    float secondBaseline = NULL;

    float CalculateBaseline();
    float calcDomFreq();

    std::string setToString(const std::set<int>& mySet);

    void EndSession();
    EEGFrequencyType DESIRED_FREQUENCY_TYPE = DELTA;
};

#endif // DEVICE_H
