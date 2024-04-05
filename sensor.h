#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>
#include <QPair>
#include "defs.h"
#include <QtMath>

class Sensor
{

public:
    Sensor(int id, EEGFrequencyType freqType);
    float ApplyTreatment(float domFreq,int round);
    float CalculateDominantFrequency();
    QVector<QPair<int, float>> getVoltageGraphData();
    std::vector<double> getFrequencyRange(EEGFrequencyType freqType);
    EEGFrequencyType getFrequencyType(float val);
    float getRandomOffset(EEGFrequencyType freqType, float val);

private:
    int id;
    QVector<float> frequencies;
    EEGFrequencyType frequencyType;
};


#endif // SENSOR_H

