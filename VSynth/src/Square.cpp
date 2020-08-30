#include "Square.h"

namespace VSynth{ namespace Waveforms {

Square::Square(int samplingRate, int tone, Sint16 amplitude)
: Waveform(samplingRate, tone, amplitude){

}

Square::~Square(){

}

Sint16 Square::nextSample(){
    Sint16 sampleValue;
    if(mSampleIndex < mNumSamples/2){
        sampleValue = mAmplitude;
    }else{
        sampleValue = -mAmplitude;
    }
    incrementSampleIndex();
    return sampleValue;
}

}};