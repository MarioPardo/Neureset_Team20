#include "sensormanager.h"

SensorManager::SensorManager() {
    for(int i= 0; i < 21; i++) {
        Sensor* newSensor = new Sensor();
        sensors.append(newSensor);
    }
}

float SensorManager::calculateAvgDomFreq() {
    float totalDomFreq = 0.0;
    for(Sensor* s: sensors) {
        totalDomFreq += s->CalculateDominantFrequency();
    }
    return totalDomFreq / sensors.size();
}

