#include "sensor.h"
#include <iostream>

Sensor::Sensor(int i) {
    id = i;
}

//fill when we know wtf is going on
float Sensor::CalculateDominantFrequency()
{
    return 0.0;
}

void Sensor::ApplyTreatment(float freq)
{
    std::cout<<"Applying treatment to Sensor#" << std::to_string(id) << " with frequency:" <<std::to_string(freq) <<std::endl;
}
