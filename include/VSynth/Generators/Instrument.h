#pragma once

#include <functional>

#include "../utils/Envelope.h"
#include "../SoundGenerator.h"

namespace VSynth
{
    /**
     * @brief Instrument representation
     * An instrument can play a variety of notes along with an Envelope.
     */
    class Instrument : public SoundGenerator
    {
    public:
        Instrument(std::function<double(double, double)> wave);

        virtual ~Instrument();

        virtual double sample(double time) = 0;

        virtual void holdNote(double frequency) = 0;
        virtual void releaseNote(double frequency) = 0;

    protected:
        std::function<double(double, double)> mWave;
    };
} // namespace VSynth