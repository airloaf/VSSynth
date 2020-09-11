#include "SawTooth.h"

#include <cmath>

namespace VSynth { namespace Oscillator {

SawTooth::SawTooth(unsigned int frequency)
: Oscillator(frequency){}

SawTooth::~SawTooth(){}

float SawTooth::generateNextSample(){
    return 2 * mFrequency * fmod(mTime, (1.0f / (float) mFrequency)) - 1;
}

}};