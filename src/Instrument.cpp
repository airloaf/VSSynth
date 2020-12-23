#include <VSynth/Instrument.h>

#include <algorithm>

namespace VSynth
{

    Instrument::Instrument(
        std::function<double(double, double)> wave,
        const ADSREnvelope &adsr)
        : mWave(wave), mADSR(adsr), mPrevSample(0)
    {
    }

    Instrument::~Instrument()
    {
    }

    double Instrument::sample(double time)
    {
        double delta = time - mPrevSample;
        mPrevSample = time;

        double sample = 0;
        if (mEnvLock.try_lock())
        {
            for (auto it = mEnvelopes.begin(); it != mEnvelopes.end(); it++)
            {
                it->second.update(delta);
                sample += mWave(it->first, time) * it->second.getAmplitude();
            }
            mEnvLock.unlock();
        }
        return sample;
    }

    void Instrument::holdNote(double frequency)
    {
        mEnvLock.lock();
        auto it = std::find_if(mEnvelopes.begin(), mEnvelopes.end(),
            [frequency](std::pair<double, Envelope> a)
                {return a.first == frequency;}
            );
        if (it == mEnvelopes.end())
        {
            mEnvelopes.push_back({frequency, Envelope(mADSR)});
            mEnvelopes.back().second.hold();
        }else{
            it->second.hold();
        }
        mEnvLock.unlock();
    }

    void Instrument::releaseNote(double frequency)
    {
        mEnvLock.lock();
        auto it = std::find_if(mEnvelopes.begin(), mEnvelopes.end(),
            [frequency](std::pair<double, Envelope> a)
                {return a.first == frequency;}
            );
        it->second.release();
        mEnvLock.unlock();
    }
} // namespace VSynth