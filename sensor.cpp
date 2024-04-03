#include "sensor.h"

#include <iostream>
#include <QThread>

Sensor::Sensor(int id, EEGFrequencyRange range): id(id), range(range) {
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

QVector<QPair<int, float>> Sensor::getVoltageGraphData() {
    qDebug() << "reachin";
    EEGFrequencyRange range = this->range;
    double minFreq, maxFreq;
    switch (range) {
        case EEGFrequencyRange::DELTA:
            minFreq = 1.0;
            maxFreq = 3.0;

            break;
        case EEGFrequencyRange::THETA:
            minFreq = 3.5;
            maxFreq = 7.5;
            break;
        case EEGFrequencyRange::ALPHA:
            minFreq = 8.0;
            maxFreq = 14.0;
            break;
        case EEGFrequencyRange::BETA:
            minFreq = 14.0;
            maxFreq = 30.0;
            break;
    }

   std::uniform_real_distribution dist(minFreq, maxFreq);
   float freqInRange = dist(*QRandomGenerator::global());

   QVector<QPair<int, float>> timeDomainSignal;

   qDebug() << freqInRange;
   for(int i = 0; i <= 60; i++) {
       float firstHarmonic = qSin(2 * float(M_PI) * (freqInRange/60 * i));
       float secondHarmonic = qSin(2 * float(M_PI) * (2 * freqInRange/60 * i));
       float thirdHarmonic = qSin(2 * float(M_PI) * (3 * freqInRange/60 * i));
       timeDomainSignal.append(QPair<int, float>(i, firstHarmonic + secondHarmonic + thirdHarmonic + 10));
   }

   qDebug() << timeDomainSignal;
   return timeDomainSignal;
}

