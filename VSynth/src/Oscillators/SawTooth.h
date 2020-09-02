#pragma once

#include "Oscillator.h"

namespace VSynth { namespace Oscillator {

class SawTooth: public Oscillator {
    public:
        SawTooth(unsigned int frequency);
        ~SawTooth();

        float nextSample(double deltaTime);
};

}};