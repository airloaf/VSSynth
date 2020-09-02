#include "Square.h"

namespace VSynth{ namespace Oscillator {

Square::Square(unsigned int frequency)
: Oscillator(frequency){}

Square::~Square(){}

float Square::nextSample(double deltaTime){
    updateTime(deltaTime);
    if(percentageComplete() < 0.5){
        return 1.0;
    }else{
        return -1.0f;
    }
}

}};