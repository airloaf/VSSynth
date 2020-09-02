#include "Sine.h"

#include <cmath>

namespace VSynth { namespace Oscillator {

Sine::Sine(unsigned int frequency)
: Oscillator(frequency){}

Sine::~Sine(){}

float toRadians(float degrees){
    return degrees * (3.14159265359f / 180.0f);
}

float Sine::nextSample(double deltaTime){
    updateTime(deltaTime);
    return sin(toRadians(percentageComplete() * 360.0f));
}

}};