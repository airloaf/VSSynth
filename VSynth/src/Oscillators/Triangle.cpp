#include "Triangle.h"

namespace VSynth { namespace Oscillator {

Triangle::Triangle(unsigned int frequency)
: Oscillator(frequency){}

Triangle::~Triangle(){}

float Triangle::nextSample(double deltaTime){
    updateTime(deltaTime);
    float percentage = percentageComplete();
    if(percentage <= 0.5){
        return -1.0f + percentage * 4.0f;
    }else{
        return 1.0f - (percentage-0.5f) * 4.0f;
    }
}

}};