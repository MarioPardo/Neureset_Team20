#ifndef DEVICE_H
#define DEVICE_H

#include "defs.h"
#include <string>
#include <set>
#include <QTime>
#include <QDateTime>
#include <QTimer>
#include <QObject>
#include "sensor.h"
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QLabel>
#include "datetimewindow.h"

class BatteryManager;
class MainMenu;
class Session;
class ActiveSessionWindow;

class Device : public QObject
{
   Q_OBJECT
public:

   Device(QObject *parent = nullptr, BatteryManager* batM = nullptr, MainMenu* mainM = nullptr,QPlainTextEdit* textEdit = nullptr,ActiveSessionWindow* activesesh = nullptr, QDateTime selectedDateTime = QDateTime());

    ~Device();

    void Display(QString);
    void SensorDisconnected(int sensor);

    void setLEDLights(QFrame* green, QFrame* blue, QFrame* red);

    void StartSession();
    void pause();
    void stop();
    void reset();
    Sensor* getSensor(int index);

    QDateTime getSelectedDateTime() const;

public slots:
    void run();


private:

    MainMenu* mainMenu;
    BatteryManager* batteryManager;
    ActiveSessionWindow* activeSessionWindow;
    QVector<Sensor*> sensors;
    QVector<Sensor*> sensorQueue;
    std::set<int> disconnectedSensors;
    int treatmentRound = -1;
    int powerPercentage = 100;
    DEVICE_STATE state = READY;
    DEVICE_STATE prevState = state;
    QTime pausedTime;
    QTime analyzedStart;
    int numRounds = 4;
    int pauseTimeout = 7000;
    int secondsRemaining;
    int analyzeTime = 5000;

    QTimer* runTimer;
    QPlainTextEdit* displayArea;

    QFrame* greenLED;
    QFrame* blueLED;
    QFrame* redLED;

    void flashFrame(QFrame* frame, std::string color);
    void updateProgress();

    float firstBaseline = -1;
    float secondBaseline = -1;

    float CalculateBaseline();
    float calcDomFreq();

    std::string setToString(const std::set<int>& mySet);

    void EndSession();

    //change this to get different frequency bands
    EEGFrequencyType DESIRED_FREQUENCY_TYPE = DELTA;

    datetimewindow* dtw;
    QDateTime selectedDateTime;
};

#endif // DEVICE_H
