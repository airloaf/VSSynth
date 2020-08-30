#include "Square.h"

namespace VSynth{ namespace Waveforms {

Square::Square(int samplingRate, int numChannels, Sint16 amplitude)
: Waveform(samplingRate, numChannels, amplitude){

}

Square::~Square(){

}

Sint16 Square::nextSample(){
    if(mSampleIndex < mNumSamples/2){
        incrementSampleIndex();
        return mAmplitude;
    }else{
        incrementSampleIndex();
        return -mAmplitude;
    }
}

}};