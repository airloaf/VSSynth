#include "Sine.h"

#include <cmath>

namespace VSynth { namespace Waveforms {

Sine::Sine(unsigned int samplingRate, unsigned int tone, Sint16 amplitude)
: Waveform(samplingRate, tone, amplitude){}

Sine::~Sine(){}

float toRadians(float degrees){
    return degrees * (3.14159265359f / 180.0f);
}

Sint16 Sine::nextSample(){
    // Calculate the degrees we are on for the sine wave
    float percentage = ((float) mSampleIndex / (float) mNumSamples);

    Sint16 sampleValue = ((float) sin(toRadians(percentage * 360.0f)) * mAmplitude);
    incrementSampleIndex();
    return sampleValue;
}

}};