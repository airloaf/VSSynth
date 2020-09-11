#include "Oscillator.h"

#define _USE_MATH_DEFINES // PI definition
#include <cmath>

namespace VSynth { namespace Oscillator{

Oscillator::Oscillator(unsigned int frequency): mTime(0), mFrequency(frequency){}
Oscillator::~Oscillator(){}

float Oscillator::nextSample(double deltaTime){
    updateTime(deltaTime);
    return generateNextSample();
}

void Oscillator::updateTime(double deltaTime){
    mTime += deltaTime;
    // since frequency is an integer number,
    // mTime only needs to be between 0 and 1,
    // so we only keep the decimal portion of this number
    mTime -= (int) mTime;
}

double Oscillator::freqToRad(){
    return mFrequency * 2.0f * M_PI;
}

}};