#include "Triangle.h"

namespace VSynth { namespace Waveforms {

Triangle::Triangle(int samplingRate, int tone, Sint16 amplitude)
: Waveform(samplingRate, tone, amplitude){

}

Triangle::~Triangle(){

}

Sint16 Triangle::nextSample(){
    Sint16 sampleValue;
    int segmentSize = (mNumSamples / 2);
    if(mSampleIndex <= (segmentSize)){ // Increasing
        float percentage = (((float) mSampleIndex) / ((float) segmentSize));
        sampleValue = -mAmplitude + percentage * 2*mAmplitude;
    }else{ // Decreasing
        float percentage = ((float) (mSampleIndex - segmentSize) / ((float) segmentSize));
        sampleValue = mAmplitude - percentage * 2*mAmplitude;
    }

    incrementSampleIndex();
    return sampleValue;
}

}};