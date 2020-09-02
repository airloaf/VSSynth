#pragma once

#include "Oscillator.h"

namespace VSynth { namespace Oscillator {

class Sine: public Oscillator {
    public:
        Sine(unsigned int frequency);
        ~Sine();

    private:
        float generateNextSample();
};

}};