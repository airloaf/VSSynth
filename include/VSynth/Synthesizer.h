#pragma once

#include <SDL2/SDL.h>

#include <functional>
#include <vector>

namespace VSynth
{

    /**
     * @brief Representation of a single instrument/voice
     * 
     * Each instrument is composed of:
     * A waveform which takes in a time and returns a value from [-1, 1]
     * An envelope to trigger the instrument
     * Amplitude to combine with the waveform
     */
    struct Instrument
    {
        std::function<double(double)> wave;
        VSynth::Envelope *envelope;
        Sint16 amplitude;
    };

    struct SynthData
    {
        double *time;
        std::vector<Instrument> instruments;
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
         * @brief Add instrument to synthesizer
         * 
         * @param instrument 
         */
        void addInstrument(const Instrument instrument);

    private:
        SDL_AudioDeviceID mDeviceID;
        double mTime;

        SynthData mSynthData;
    };

}; // namespace VSynth