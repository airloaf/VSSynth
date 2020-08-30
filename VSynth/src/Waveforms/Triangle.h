#pragma once

#include "Waveform.h"

namespace VSynth { namespace Waveforms {

class Triangle: public Waveform {
    public:
        Triangle(unsigned int samplingRate, unsigned int tone, Sint16 amplitude);
        ~Triangle();

        Sint16 nextSample();
};

}};