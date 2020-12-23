#pragma once

#include <SDL2/SDL.h>

#include <functional>
#include <vector>

#include "Envelope.h"
#include "SoundGenerator.h"

namespace VSynth
{

    struct SynthData
    {
        double *time;
        std::vector<SoundGenerator *> soundGenerators;
    };

    /**
     * @brief Entrypoint and interface for audio synthesis
     * 
     * Creates a software synthesizer. The synthesizer can be manipulated by adding instruments.
     */
    class Synthesizer
    {
    public:
        Synthesizer();
        ~Synthesizer();

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

    private:
        SDL_AudioDeviceID mDeviceID;
        double mTime;

        SynthData mSynthData;
    };

}; // namespace VSynth