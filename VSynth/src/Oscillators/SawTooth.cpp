#include "SawTooth.h"

namespace VSynth { namespace Oscillator {

SawTooth::SawTooth(unsigned int frequency)
: Oscillator(frequency){}

SawTooth::~SawTooth(){}

float SawTooth::nextSample(double deltaTime){
    updateTime(deltaTime);
    return -1.0f + percentageComplete() * 2.0f;
}

}};