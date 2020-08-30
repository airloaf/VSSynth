#pragma once

#include "Waveform.h"

namespace VSynth { namespace Waveforms {

class Sine: public Waveform {
    public:
        Sine(unsigned int samplingRate, unsigned int tone, Sint16 amplitude);
        ~Sine();

        Sint16 nextSample();
};

}};