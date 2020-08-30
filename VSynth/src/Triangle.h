#pragma once

#include "Waveform.h"

namespace VSynth { namespace Waveforms {

class Triangle: public Waveform {
    public:
        Triangle(int samplingRate, int tone, Sint16 amplitude);
        ~Triangle();

        Sint16 nextSample();
};

}};