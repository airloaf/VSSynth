#pragma once

#include "Waveform.h"

namespace VSynth{ namespace Waveforms{

class Square: public Waveform {
    public:
        Square(int samplingRate, int numChannels, Sint16 amplitude);
        ~Square();

        Sint16 nextSample();
};

}};