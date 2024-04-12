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
    void ApplyTreatment(float domFreq,int round);
    float CalculateDominantFrequency();
    void generateFrequenciesAndAmplitudes(float targetFrequency = -1);
    QVector<QPair<int, float>> generateVoltageGraphData();
    std::vector<double> getFrequencyRange(EEGFrequencyType freqType);
    EEGFrequencyType getFrequencyType(float freq);
    float generateNewFrequency();


private:
    int id;
    QVector<float> frequencies;
    EEGFrequencyType frequencyType;
    int amplitude1;
    int amplitude2;
    int amplitude3;
    float frequency1;
    float frequency2;
    float frequency3;
};


#endif // SENSOR_H

