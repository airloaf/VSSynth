#pragma once

#include "Waveform.h"

namespace VSynth { namespace Waveforms {

class SawTooth: public Waveform {
    public:
        SawTooth(unsigned int samplingRate, unsigned int tone, Sint16 amplitude);
        ~SawTooth();

        Sint16 nextSample();
};

}};