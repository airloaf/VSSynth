#pragma once

#include <functional>
#include <mutex>
#include <vector>

#include "Instrument.h"

namespace VSynth
{
    class PolyphonicInstrument : public Instrument
    {
    public:
        PolyphonicInstrument(
            std::function<double(double, double)> wave,
            const ADSREnvelope &adsr);

        virtual ~PolyphonicInstrument();

        double sample(double time);

        void holdNote(double frequency);
        void releaseNote(double frequency);

    private:
        std::mutex mEnvLock;
        std::vector<std::pair<double, Envelope>> mEnvelopes;

        double mPrevSample;
    };
} // namespace VSynth