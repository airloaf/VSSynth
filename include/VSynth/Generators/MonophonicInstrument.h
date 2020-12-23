#pragma once

#include <functional>
#include <mutex>
#include <vector>

#include "Instrument.h"

namespace VSynth
{
    class MonophonicInstrument : public Instrument
    {
    public:
        MonophonicInstrument(
            std::function<double(double, double)> wave,
            const ADSREnvelope &adsr);

        virtual ~MonophonicInstrument();

        double sample(double time);

        void holdNote(double frequency);
        void releaseNote(double frequency);

    private:
        Envelope mEnvelope;

        double mCurrentNote;
        double mPrevSample;
    };
} // namespace VSynth
