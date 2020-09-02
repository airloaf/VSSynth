#include "Oscillator.h"

#include <cmath>

namespace VSynth { namespace Oscillator{

Oscillator::Oscillator(unsigned int frequency): mTime(0){
    mDuration = 1000000.0f / frequency;
    reset();
}

Oscillator::~Oscillator(){}

float Oscillator::nextSample(double deltaTime){
    updateTime(deltaTime);
    return generateNextSample();
}

float Oscillator::percentageComplete(){
    return (float) mTime / (float) mDuration;
}

void Oscillator::updateTime(double deltaTime){
    mTime = fmod(mTime + deltaTime, mDuration);
}

void Oscillator::reset(){
    mTime = 0;
}

}};