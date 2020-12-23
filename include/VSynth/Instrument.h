#pragma once

#include <functional>
#include <mutex>
#include <vector>

#include <VSynth/Envelope.h>

#include "SoundGenerator.h"

namespace VSynth
{
    /**
     * @brief Instrument
     * An instrument is defined as a class which can play a variety of notes along with an Envelope
     */
    class Instrument : public SoundGenerator
    {
    public:
        Instrument(std::function<double(double, double)> wave, const ADSREnvelope &adsr);
        virtual ~Instrument();

        virtual double sample(double time);

        virtual void holdNote(double frequency);
        virtual void releaseNote(double frequency);

    private:
        ADSREnvelope mADSR;
        
        std::function<double(double, double)> mWave;
        std::mutex mEnvLock;
        std::vector<std::pair<double, Envelope>> mEnvelopes;

        double mPrevSample;
    };
} // namespace VSynth