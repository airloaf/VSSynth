#include "SawTooth.h"

namespace VSynth { namespace Oscillator {

SawTooth::SawTooth(unsigned int frequency)
: Oscillator(frequency){}

SawTooth::~SawTooth(){}

float SawTooth::generateNextSample(){
    return -1.0f + percentageComplete() * 2.0f;
}

}};