#include "Waveform.h"

namespace VSynth { namespace Waveforms{

Waveform::Waveform(unsigned int samplingRate, unsigned int tone, Sint16 amplitude){
    mAmplitude = amplitude;
    mNumSamples = samplingRate / (tone);

    reset();
}

Waveform::~Waveform(){

}

void Waveform::incrementSampleIndex(){
    mSampleIndex = (mSampleIndex + 1) % mNumSamples;
}

void Waveform::reset(){
    mSampleIndex = 0;
}

}};