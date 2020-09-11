#include "Square.h"

#include <cmath>

namespace VSynth{ namespace Oscillator {

Square::Square(unsigned int frequency)
: Oscillator(frequency){}
Square::~Square(){}

float Square::generateNextSample(){
    return sin(freqToRad() * mTime) > 0.0f? 1.0f: -1.0f;
}

}};