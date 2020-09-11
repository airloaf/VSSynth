#include "Triangle.h"

#include <cmath>

namespace VSynth { namespace Oscillator {

Triangle::Triangle(unsigned int frequency)
: Oscillator(frequency){}
Triangle::~Triangle(){}

float Triangle::generateNextSample(){
    return asin(sin(freqToRad() * mTime));
}

}};