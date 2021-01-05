#pragma once

#include <SDL2/SDL.h>

#include <functional>
#include <vector>

#include "SoundGenerator.h"
#include "SynthMiddleware.h"

namespace VSynth
{
    struct SynthData
    {
        double *time;
        double sampleDeltaTime;
        std::vector<SoundGenerator *> soundGenerators;
        std::vector<SynthMiddleware *> middleware;
    };

    /**
     * @brief Entrypoint and interface for audio synthesis
     * 
     * Creates a software synthesizer. The synthesizer can be manipulated by adding instruments.
     */
    class Synthesizer
    {
    public:
        /**
         * @brief Construct a new Synthesizer object
         * 
         * @param samplingRates - Sampling rate (# of samples per second). 48,000 is a common number, but higher values are computationally intensive
         * @param numFrames - Number of sampling frames. A sampling frame is an instance where sound generators are sampled. 
         */
        Synthesizer(unsigned int samplingRates = 48000, unsigned int numFrames = 20);
        virtual ~Synthesizer();

        /**
         * @brief Creates the internal audio device
         * 
         */
        void open();

        /**
         * @brief Destroys the internal audio device
         * 
         */
        void close();

        /**
         * @brief Unpauses the synthesizer
         * 
         * Sound will resume if the synthesizer has been paused
         */
        void unpause();

        /**
         * @brief Pauses the synthesizer
         * 
         * Sound will stop if the synthesizer is currently running
         */
        void pause();

        /**
         * @brief Adds a sound generator to the synthesizer
         * 
         * @param soundGenerator 
         */
        void addSoundGenerator(SoundGenerator *soundGenerator);

        /**
         * @brief Adds a middleware to the synthesizer
         * 
         * @param middleware 
         */
        void addMiddleware(SynthMiddleware *middleware);

    private:
        SDL_AudioDeviceID mDeviceID;

        double mTime;

        unsigned int mSamplingRate;
        unsigned int mNumFrames;

        SynthData mSynthData;
    };

}; // namespace VSynth