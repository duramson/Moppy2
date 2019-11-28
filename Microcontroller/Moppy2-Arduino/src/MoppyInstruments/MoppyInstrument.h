/*
 * MoppyInstrument.h
 * Stores useful constants for MoppyInstrument implementations
 */

#ifndef MOPPY_SRC_MOPPYINSTRUMENTS_MOPPYINSTRUMENT_H_
#define MOPPY_SRC_MOPPYINSTRUMENTS_MOPPYINSTRUMENT_H_

#include <Arduino.h>
#include "../MoppyMessageConsumer.h"

// Number of octaves to bend notes by at full-deflection (MIDI pitch bending is weird).
// Described as cents/cents-in-an-octave
#define BEND_OCTAVES 200 / (float)1200

/*
 * Number of microseconds in a timer-tick for setting timer resolution
 * and calculating noteTicks.  Smaller values here will trigger interrupts more often,
 * which might interfere with other processes but will result in more accurate frequency
 * reproduction.
 */
#define TIMER_RESOLUTION 20

// In some cases a pulse will only happen every-other tick (e.g. if the tick is
// toggling a pin on and off and pulses happen on rising signal) so to simplify
// the already ugly arrays below, multiply the RESOLUTION by 2 here.
#define DOUBLE_T_RESOLUTION (TIMER_RESOLUTION * 2)

// The period of notes in microseconds
const unsigned int notePeriods[128] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    30578, 28861, 27242, 25713, 24270, 22909, 21622, 20409, 19263, 18182, 17161, 16198, //C1 - B1
    15289, 14436, 13621, 12856, 12135, 11454, 10811, 10205, 9632, 9091, 8581, 8099,     //C2 - B2
    7645, 7218, 6811, 6428, 6068, 5727, 5406, 5103, 4816, 4546, 4291, 4050,             //C3 - B3
    3823, 3609, 3406, 3214, 3034, 2864, 2703, 2552, 2408, 2273, 2146, 2025,             //C4 - B4
    1911, 1804, 1703, 1607, 1517, 1432, 1351, 1276, 1204, 1136, 1073, 1012,             //C5 - B5
    956, 902, 851, 804, 758, 716, 676, 638, 602, 568, 536, 506,                         //C6 - B6
    478, 451, 426, 402, 379, 358, 338, 319, 301, 284, 268, 253,                         //C7 - B7
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0};

// NOTE: Yes this is super ugly, but it avoids having to calculate this at runtime.  Changes
// to notePeriods above will require matching changes here
// The period of notes in two-tick units
const unsigned int noteDoubleTicks[128] = {
    0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION,
    0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION,
    30578 / DOUBLE_T_RESOLUTION, 28861 / DOUBLE_T_RESOLUTION, 27242 / DOUBLE_T_RESOLUTION, 25713 / DOUBLE_T_RESOLUTION, 24270 / DOUBLE_T_RESOLUTION, 22909 / DOUBLE_T_RESOLUTION, 21622 / DOUBLE_T_RESOLUTION, 20409 / DOUBLE_T_RESOLUTION, 19263 / DOUBLE_T_RESOLUTION, 18182 / DOUBLE_T_RESOLUTION, 17161 / DOUBLE_T_RESOLUTION, 16198 / DOUBLE_T_RESOLUTION, //C1 - B1
    15289 / DOUBLE_T_RESOLUTION, 14436 / DOUBLE_T_RESOLUTION, 13621 / DOUBLE_T_RESOLUTION, 12856 / DOUBLE_T_RESOLUTION, 12135 / DOUBLE_T_RESOLUTION, 11454 / DOUBLE_T_RESOLUTION, 10811 / DOUBLE_T_RESOLUTION, 10205 / DOUBLE_T_RESOLUTION, 9632 / DOUBLE_T_RESOLUTION, 9091 / DOUBLE_T_RESOLUTION, 8581 / DOUBLE_T_RESOLUTION, 8099 / DOUBLE_T_RESOLUTION,     //C2 - B2
    7645 / DOUBLE_T_RESOLUTION, 7218 / DOUBLE_T_RESOLUTION, 6811 / DOUBLE_T_RESOLUTION, 6428 / DOUBLE_T_RESOLUTION, 6068 / DOUBLE_T_RESOLUTION, 5727 / DOUBLE_T_RESOLUTION, 5406 / DOUBLE_T_RESOLUTION, 5103 / DOUBLE_T_RESOLUTION, 4816 / DOUBLE_T_RESOLUTION, 4546 / DOUBLE_T_RESOLUTION, 4291 / DOUBLE_T_RESOLUTION, 4050 / DOUBLE_T_RESOLUTION,             //C3 - B3
    3823 / DOUBLE_T_RESOLUTION, 3609 / DOUBLE_T_RESOLUTION, 3406 / DOUBLE_T_RESOLUTION, 3214 / DOUBLE_T_RESOLUTION, 3034 / DOUBLE_T_RESOLUTION, 2864 / DOUBLE_T_RESOLUTION, 2703 / DOUBLE_T_RESOLUTION, 2552 / DOUBLE_T_RESOLUTION, 2408 / DOUBLE_T_RESOLUTION, 2273 / DOUBLE_T_RESOLUTION, 2146 / DOUBLE_T_RESOLUTION, 2025 / DOUBLE_T_RESOLUTION,             //C4 - B4
    1911 / DOUBLE_T_RESOLUTION, 1804 / DOUBLE_T_RESOLUTION, 1703 / DOUBLE_T_RESOLUTION, 1607 / DOUBLE_T_RESOLUTION, 1517 / DOUBLE_T_RESOLUTION, 1432 / DOUBLE_T_RESOLUTION, 1351 / DOUBLE_T_RESOLUTION, 1276 / DOUBLE_T_RESOLUTION, 1204 / DOUBLE_T_RESOLUTION, 1136 / DOUBLE_T_RESOLUTION, 1073 / DOUBLE_T_RESOLUTION, 1012 / DOUBLE_T_RESOLUTION,             //C5 - B5
    956 / DOUBLE_T_RESOLUTION, 902 / DOUBLE_T_RESOLUTION, 851 / DOUBLE_T_RESOLUTION, 804 / DOUBLE_T_RESOLUTION, 758 / DOUBLE_T_RESOLUTION, 716 / DOUBLE_T_RESOLUTION, 676 / DOUBLE_T_RESOLUTION, 638 / DOUBLE_T_RESOLUTION, 602 / DOUBLE_T_RESOLUTION, 568 / DOUBLE_T_RESOLUTION, 536 / DOUBLE_T_RESOLUTION, 506 / DOUBLE_T_RESOLUTION,                         //C6 - B6
    478 / DOUBLE_T_RESOLUTION, 451 / DOUBLE_T_RESOLUTION, 426 / DOUBLE_T_RESOLUTION, 402 / DOUBLE_T_RESOLUTION, 379 / DOUBLE_T_RESOLUTION, 358 / DOUBLE_T_RESOLUTION, 338 / DOUBLE_T_RESOLUTION, 319 / DOUBLE_T_RESOLUTION, 301 / DOUBLE_T_RESOLUTION, 284 / DOUBLE_T_RESOLUTION, 268 / DOUBLE_T_RESOLUTION, 253 / DOUBLE_T_RESOLUTION,                         //C7 - B7
    0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION,
    0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0 / DOUBLE_T_RESOLUTION, 0};

const unsigned int noteTicks[128] = {
    0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION,
    0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION,
    30578 / TIMER_RESOLUTION, 28861 / TIMER_RESOLUTION, 27242 / TIMER_RESOLUTION, 25713 / TIMER_RESOLUTION, 24270 / TIMER_RESOLUTION, 22909 / TIMER_RESOLUTION, 21622 / TIMER_RESOLUTION, 20409 / TIMER_RESOLUTION, 19263 / TIMER_RESOLUTION, 18182 / TIMER_RESOLUTION, 17161 / TIMER_RESOLUTION, 16198 / TIMER_RESOLUTION, //C1 - B1
    15289 / TIMER_RESOLUTION, 14436 / TIMER_RESOLUTION, 13621 / TIMER_RESOLUTION, 12856 / TIMER_RESOLUTION, 12135 / TIMER_RESOLUTION, 11454 / TIMER_RESOLUTION, 10811 / TIMER_RESOLUTION, 10205 / TIMER_RESOLUTION, 9632 / TIMER_RESOLUTION, 9091 / TIMER_RESOLUTION, 8581 / TIMER_RESOLUTION, 8099 / TIMER_RESOLUTION,     //C2 - B2
    7645 / TIMER_RESOLUTION, 7218 / TIMER_RESOLUTION, 6811 / TIMER_RESOLUTION, 6428 / TIMER_RESOLUTION, 6068 / TIMER_RESOLUTION, 5727 / TIMER_RESOLUTION, 5406 / TIMER_RESOLUTION, 5103 / TIMER_RESOLUTION, 4816 / TIMER_RESOLUTION, 4546 / TIMER_RESOLUTION, 4291 / TIMER_RESOLUTION, 4050 / TIMER_RESOLUTION,             //C3 - B3
    3823 / TIMER_RESOLUTION, 3609 / TIMER_RESOLUTION, 3406 / TIMER_RESOLUTION, 3214 / TIMER_RESOLUTION, 3034 / TIMER_RESOLUTION, 2864 / TIMER_RESOLUTION, 2703 / TIMER_RESOLUTION, 2552 / TIMER_RESOLUTION, 2408 / TIMER_RESOLUTION, 2273 / TIMER_RESOLUTION, 2146 / TIMER_RESOLUTION, 2025 / TIMER_RESOLUTION,             //C4 - B4
    1911 / TIMER_RESOLUTION, 1804 / TIMER_RESOLUTION, 1703 / TIMER_RESOLUTION, 1607 / TIMER_RESOLUTION, 1517 / TIMER_RESOLUTION, 1432 / TIMER_RESOLUTION, 1351 / TIMER_RESOLUTION, 1276 / TIMER_RESOLUTION, 1204 / TIMER_RESOLUTION, 1136 / TIMER_RESOLUTION, 1073 / TIMER_RESOLUTION, 1012 / TIMER_RESOLUTION,             //C5 - B5
    956 / TIMER_RESOLUTION, 902 / TIMER_RESOLUTION, 851 / TIMER_RESOLUTION, 804 / TIMER_RESOLUTION, 758 / TIMER_RESOLUTION, 716 / TIMER_RESOLUTION, 676 / TIMER_RESOLUTION, 638 / TIMER_RESOLUTION, 602 / TIMER_RESOLUTION, 568 / TIMER_RESOLUTION, 536 / TIMER_RESOLUTION, 506 / TIMER_RESOLUTION,                         //C6 - B6
    478 / TIMER_RESOLUTION, 451 / TIMER_RESOLUTION, 426 / TIMER_RESOLUTION, 402 / TIMER_RESOLUTION, 379 / TIMER_RESOLUTION, 358 / TIMER_RESOLUTION, 338 / TIMER_RESOLUTION, 319 / TIMER_RESOLUTION, 301 / TIMER_RESOLUTION, 284 / TIMER_RESOLUTION, 268 / TIMER_RESOLUTION, 253 / TIMER_RESOLUTION,                         //C7 - B7
    0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION,
    0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0 / TIMER_RESOLUTION, 0};

class MoppyInstrument : public MoppyMessageConsumer
{
public:
    virtual void setup() = 0;
};

#endif /* MOPPY_SRC_MOPPYINSTRUMENTS_MOPPYINSTRUMENT_H_ */
