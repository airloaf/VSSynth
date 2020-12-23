#include <VSynth/Generators/MonophonicInstrument.h>

#include <algorithm>

namespace VSynth
{

    MonophonicInstrument::MonophonicInstrument(
        std::function<double(double, double)> wave,
        const ADSREnvelope &adsr)
        : Instrument(wave, adsr), mEnvelope(adsr), mPrevSample(0)
    {
    }

    MonophonicInstrument::~MonophonicInstrument()
    {
    }

    double MonophonicInstrument::sample(double time)
    {
        double delta = time - mPrevSample;
        mPrevSample = time;

        double sample = 0;
        mEnvelope.update(delta);
        sample += mWave(mCurrentNote, time) * mEnvelope.getAmplitude();

        return sample;
    }

    void MonophonicInstrument::holdNote(double frequency)
    {
        mCurrentNote = frequency;
        mEnvelope.hold();
    }

    void MonophonicInstrument::releaseNote(double frequency)
    {
        mEnvelope.release();
    }
} // namespace VSynth