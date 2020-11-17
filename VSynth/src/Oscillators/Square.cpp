#include "Square.h"

#include <cmath>

namespace VSynth{ namespace Oscillator {

Square::Square(unsigned int frequency)
: Oscillator(frequency){}
Square::~Square(){}

float Square::generateNextSample(){
    //return sin(freqToRad() * mTime) > 0.0f? 1.0f: -1.0f;
    double period = 1.0 / (double) mFrequency;
    if(fmod(mTime, period) < (period * 0.9)){
        return -1.0f;
    }else{
        return 1.0f;
    }
}

}};