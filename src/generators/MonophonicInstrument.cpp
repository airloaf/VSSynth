#include <VSynth/generators/MonophonicInstrument.h>

#include <algorithm>

namespace VSynth
{
    namespace Generators
    {

        MonophonicInstrument::MonophonicInstrument(
            std::function<double(double, double)> wave,
            const ADSREnvelope &adsr)
            : Instrument(wave), mEnvelope(adsr), mPrevSample(0)
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
            if (mCurrentNote == frequency)
            {
                mEnvelope.release();
            }
        }
    } // namespace Generators
} // namespace VSynth