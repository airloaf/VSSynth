#include "SawTooth.h"

namespace VSynth { namespace Waveforms {

SawTooth::SawTooth(int samplingRate, int tone, Sint16 amplitude)
: Waveform(samplingRate, tone, amplitude){}

SawTooth::~SawTooth(){}

Sint16 SawTooth::nextSample(){
    Sint16 sampleValue = -mAmplitude + (Sint16) (((float) mSampleIndex / (float) mNumSamples) * (float) mAmplitude);
    incrementSampleIndex();
    return sampleValue;
}

}};