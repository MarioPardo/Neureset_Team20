#include "sensor.h"

#include <iostream>
#include <QThread>

Sensor::Sensor(int i) {
    id = i;
}

//fill when we know wtf is going on
float Sensor::CalculateDominantFrequency()
{
    return 5; //rand value for now
}


float Sensor::ApplyTreatment(float domFreq, int round)
{
    std::cout<<"Applying treatment to Sensor#" << std::to_string(id) << " with dominant frequency:" <<std::to_string(domFreq) <<std::endl;


    for(int i = 0; i < 16; i++)
    {
        int tempFreq = domFreq;

        if(i % 2 == 1)
            tempFreq = domFreq + (5*round);

        std::cout<<"    Frequency at " << std::to_string(tempFreq) << "hz" <<std::endl;;
        QThread::msleep(62);
    }

    int randOffset = 2; //TODO implement proper random offset

    return domFreq + randOffset;

}



