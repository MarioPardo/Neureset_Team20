#include "sensor.h"
#include <iostream>
#include <QThread>
#include <random>

Sensor::Sensor(int id, EEGFrequencyType freqType): id(id), frequencyType(freqType) {
    generateFrequenciesAndAmplitudes();
}

float Sensor::CalculateDominantFrequency()
{
    double amp1Squared = amplitude1 * amplitude1;
    double amp2Squared = amplitude2 * amplitude2;
    double amp3Squared = amplitude3 * amplitude3;
    float domFreq = ((frequency1 * amp1Squared) + (frequency2 * amp2Squared) + (frequency3 * amp3Squared))/(amp1Squared + amp2Squared + amp3Squared);
    return domFreq;
}

std::vector<double> Sensor::getFrequencyRange(EEGFrequencyType freqType) {
    double minFreq, maxFreq;

    switch (freqType) {
    case EEGFrequencyType::DELTA:
        minFreq = 1.0;
        maxFreq = 4.0;
        break;
        case EEGFrequencyType::THETA:
        minFreq = 4.0;
        maxFreq = 8.0;
        break;
    case EEGFrequencyType::ALPHA:
        minFreq = 8.0;
        maxFreq = 12.0;
        break;
    case EEGFrequencyType::BETA:
        minFreq = 12.0;
        maxFreq = 30.0;
        break;
    }

    std::vector<double> rangeVec = {minFreq, maxFreq};
    return rangeVec;
}

EEGFrequencyType Sensor::getFrequencyType(float freq) {
    if (freq >= 1.0 && freq <= 4.0) {
        return EEGFrequencyType::DELTA;
    } else if (freq >= 4.0 && freq <= 8.0) {
        return EEGFrequencyType::THETA;
    } else if (freq >= 8.0 && freq <= 12.0) {
        return EEGFrequencyType::ALPHA;
    } else if (freq >= 12.0 && freq <= 30.0) {
        return EEGFrequencyType::BETA;
    } else {
        return EEGFrequencyType::BETA;
    }
}

float Sensor::generateNewFrequency()
{
    std::vector<double> ranges = this->getFrequencyRange(this->frequencyType);
    double minFreq = ranges[0];
    double maxFreq = ranges[1];
    //[----I-----]  bottom range, from [ to first harmonic frequency (this actually represents target freq. of wave)
    std::uniform_real_distribution<double> dis(minFreq, maxFreq);
    double newFreq =dis(*QRandomGenerator::global());
    frequency1 = newFreq;
    //return random number with frequency w would reduce brain activity
    return newFreq;
}

void Sensor::ApplyTreatment(float domFreq, int round)
{
    std::cout<<"Applying treatment to Sensor#" << std::to_string(id) << " with dominant frequency:" <<std::to_string(domFreq) << "\n" ;


    for(int i = 0; i < 16; i++)
    {
        float tempFreq = domFreq;

        if(i % 2 == 1)
            tempFreq = domFreq + (5*round);

        // std::cout<<"Sensor " << std::to_string(this->id) + " frequency at " << std::to_string(tempFreq) << "hz" <<std::endl;;
        //63 milisecond sleep because 1/16th of a second = 62.5 milliseconds but you can't pass floats or doubles into msleep
        QThread::msleep(63);
    }
}

void Sensor::generateFrequenciesAndAmplitudes(float targetFrequency) {
    int minAmp, maxAmp;

    if(targetFrequency == -1) {
        EEGFrequencyType range = this->frequencyType;

        double minFreq, maxFreq;

        //TODO change to use getFrequencyRange()

        std::vector<double> freqRange = getFrequencyRange(range);
        minFreq = freqRange.at(0);
        maxFreq = freqRange.at(1);

        //generate frequency within the sensor's range in order to
        std::uniform_real_distribution freq_dist(minFreq, maxFreq);
        targetFrequency = freq_dist(*QRandomGenerator::global());
    }


    switch(this->frequencyType) {
        case DELTA:
            minAmp = 1;
            maxAmp = 2;
            break;
        case THETA:
            minAmp = 1;
            maxAmp = 3;
            break;
        case ALPHA:
            minAmp = 2;
            maxAmp = 4;
            break;
        case BETA:
            minAmp = 3;
            maxAmp = 5;
            break;
    }

   std::uniform_int_distribution<int> amp_dist(minAmp, maxAmp);
   // Generate random numbers between 1-3 for amplitudes
   this->amplitude1 = amp_dist(*QRandomGenerator::global());
   this->amplitude2 = amp_dist(*QRandomGenerator::global());
   this->amplitude3 = amp_dist(*QRandomGenerator::global());

   //create harmonic frequencies for waves based on randomly generated frequency - this helps generate waveform data given these frequencies and amplitudes.
   this->frequency1 = targetFrequency;
   this->frequency2 = 2 * targetFrequency;
   this->frequency3 = 3 * targetFrequency;


}

QVector<QPair<int, float>> Sensor::generateVoltageGraphData() {
    QVector<QPair<int, float>> timeDomainSignal;
    for(int i = 0; i <= 60; i++) {
        //sampling rate of 120 - 2 * the number of seconds in a minute.
        float firstHarmonic = amplitude1 * qSin(2 * float(M_PI) * (frequency1/120 * i));
        float secondHarmonic = amplitude2 *  qSin(2 * float(M_PI) * (2 * frequency2/120 * i));
        float thirdHarmonic = amplitude3 * qSin(2 * float(M_PI) * (3 * frequency3/120 * i));
        timeDomainSignal.append(QPair<int, float>(i, firstHarmonic + secondHarmonic + thirdHarmonic + 15));
    }
    return timeDomainSignal;
}

