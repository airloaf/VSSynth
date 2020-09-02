#pragma once

#include "Oscillator.h"

namespace VSynth { namespace Oscillator {

class Triangle: public Oscillator {
    public:
        Triangle(unsigned int frequency);
        ~Triangle();

    private:
        float generateNextSample();
};

}};