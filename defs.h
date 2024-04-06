#ifndef DEFS_H
#define DEFS_H

enum DEVICE_STATE {
    READY = 0,
    IN_SESSION = 1,
    PAUSED = 2,
    STOPPED  = 3,

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

#define DRAIN_RATE_FAST 3;
#define DRAIN_RATE_SLOW  1;

#endif

