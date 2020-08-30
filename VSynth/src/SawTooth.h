#pragma once

#include "Waveform.h"

namespace VSynth { namespace Waveforms {

class SawTooth: public Waveform {
    public:
        SawTooth(int samplingRate, int tone, Sint16 amplitude);
        ~SawTooth();

        Sint16 nextSample();
};

}};