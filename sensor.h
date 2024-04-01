#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QVector>


class Sensor
{

public:
    Sensor(int i);
    float ApplyTreatment(float domFreq, int round);
    float CalculateDominantFrequency();

private:
    int id;
    QVector<float> frequencies;

};


#endif // SENSOR_H

