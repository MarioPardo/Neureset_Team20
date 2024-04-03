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

enum EEGFrequencyRange {
    DELTA,
    THETA,
    ALPHA,
    BETA
};

#endif
// EEGFrequencyRange getRange(double value) {
//     if (value >= 1 && value <= 3)
//         return EEGFrequencyRange::DELTA;
//     else if (value >= 3.5 && value <= 7.5)
//         return EEGFrequencyRange::THETA;
//     else if (value >= 7.5 && value <= 13)
//         return EEGFrequencyRange::ALPHA;
//     else
//         return EEGFrequencyRange::BETA;
// }
