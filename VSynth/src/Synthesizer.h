#pragma once

#include <SDL2/SDL.h>
#include <list>

namespace VSynth{

    struct Instrument
    {
        std::function<double(double)> wave;
        VSynth::Envelope *envelope;
        Sint16 amplitude;
    };

    struct SynthData {
        double *time;
        std::list<Instrument> instruments;
    };

    class Synthesizer{
        public:

            Synthesizer();
            ~Synthesizer();

            void open();
            void close();

            void unpause();
            void pause();

            void addInstrument(const Instrument instrument);

        private:
            SDL_AudioDeviceID mDeviceID;
            double mTime;

            SynthData mSynthData;

    };

};