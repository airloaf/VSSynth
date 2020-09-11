#include "Sine.h"

#include <cmath>

namespace VSynth { namespace Oscillator {

Sine::Sine(unsigned int frequency)
: Oscillator(frequency) {}
Sine::~Sine(){}

float Sine::generateNextSample(){
    return sin(freqToRad() * mTime);
}

}};