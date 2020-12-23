#pragma once

#include <functional>
#include <mutex>
#include <vector>

#include "Instrument.h"

namespace VSynth
{
    /**
     * @brief Device capable of playing notes simultaneously
     * A polyphonic instrument is capable of playing
     * multiple notes simultaneously. Real life examples
     * include: stringed instruments, piano and certain
     * percussive instruments like the xylophone.
     * 
     */
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
        ADSREnvelope mADSR;

        std::mutex mEnvLock;
        std::vector<std::pair<double, Envelope>> mEnvelopes;

        double mPrevSample;
    };
} // namespace VSynth