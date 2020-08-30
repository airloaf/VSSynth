#pragma once

#include <SDL2/SDL.h>

namespace VSynth{ namespace Waveforms{

/**
 * @brief Waveform representation
 */
class Waveform{
    public:
        Waveform(unsigned unsigned int samplingRate, unsigned unsigned int tone, Sint16 amplitude);
        ~Waveform();

        /**
         * @brief Get the next sample for the waveform
         * @return Sint16 
         */
        virtual Sint16 nextSample() = 0;

        /**
         * @brief Resets the waveform
         */
        void reset();

    protected:
        void incrementSampleIndex();

        Sint16 mAmplitude;
        unsigned int mNumSamples;
        unsigned int mSampleIndex;
};

}};