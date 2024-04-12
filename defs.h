#ifndef DEFS_H
#define DEFS_H

enum DEVICE_STATE {
    READY = 0,
    PAUSED = 2,

    //for running treatment
    FIRST_OVERALL = 4,
    APPLYING_TREATMENT = 5,
    SECOND_OVERALL = 6,
};

enum EEGFrequencyType {
    DELTA,
    THETA,
    ALPHA,
    BETA
};

#define DRAIN_RATE_DELAY 3000

#define DRAIN_RATE_FAST 2
#define DRAIN_RATE_SLOW  1

#define SESSION_LENGTH 35

#define NUM_SENSORS 7

#endif

