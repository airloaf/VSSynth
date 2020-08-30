#pragma once

#include "Waveform.h"

namespace VSynth{ namespace Waveforms{

class Square: public Waveform {
    public:
        Square(unsigned int samplingRate, unsigned int tone, Sint16 amplitude);
        ~Square();

        Sint16 nextSample();
};

}};