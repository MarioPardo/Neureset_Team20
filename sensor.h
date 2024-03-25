#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

class Sensor
{
    Q_OBJECT

public:
    Sensor();
    float CalculateDominantFrequency();

private:
    int id;
    QVector<float> frequencies;

};


#endif // SENSOR_H

