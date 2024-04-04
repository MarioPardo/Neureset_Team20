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
    Sensor(int id, EEGFrequencyRange range);
    float ApplyTreatment(float domFreq,int round);
    float CalculateDominantFrequency();
    QVector<QPair<int, float>> getVoltageGraphData();
private:
    int id;
    QVector<float> frequencies;
    EEGFrequencyRange range;
};


#endif // SENSOR_H

