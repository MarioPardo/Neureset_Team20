#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

class Sensor
{

public:
    Sensor();
    float CalculateDominantFrequency();

private:
    int id;
    QVector<float> frequencies;

};


#endif // SENSOR_H

