#pragma once

#include "Oscillator.h"

namespace VSynth{ namespace Oscillator {

class Square: public Oscillator {
    public:
        Square(unsigned int frequency);
        ~Square();

        float generateNextSample();
};

}};