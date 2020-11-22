#include <SDL2/SDL.h>
#include <vector>

#include "Envelope.h"
#include "Waveforms.h"

#include "Synthesizer.h"

using namespace VSynth;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window *window;
    window = SDL_CreateWindow("SDL_Test_Windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    Synthesizer synth;
    synth.open();

    ADSREnvelope pianoADSR(0.90f, 0.60f, 0.20f, 0.20f, 0.50f);
    Envelope e4Envelope(pianoADSR);
    Envelope f4Envelope(pianoADSR);

    std::function<double(double)> freqOsc = std::bind(Waveforms::sine, 10, std::placeholders::_1);

    Instrument e4;
    e4.wave = std::bind(Waveforms::modulatedWave,
                        Waveforms::square,
                        330.0,
                        0.01,
                        freqOsc,
                        std::placeholders::_1
                        );
    e4.amplitude = 3000;
    e4.envelope = &e4Envelope;

    Instrument f4;
    f4.wave = std::bind(Waveforms::modulatedWave,
                        Waveforms::square,
                        350.0,
                        0.01,
                        freqOsc,
                        std::placeholders::_1
                        );
    f4.amplitude = 3000;
    f4.envelope = &f4Envelope;

    synth.addInstrument(e4);
    synth.addInstrument(f4);

    synth.unpause();

    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0)
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_e)
                {
                    e4Envelope.hold();
                }
                else if (e.key.keysym.sym == SDLK_f)
                {
                    f4Envelope.hold();
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_e)
                {
                    e4Envelope.release();
                }
                else if (e.key.keysym.sym == SDLK_f)
                {
                    f4Envelope.release();
                }
            }
        }
    }

    synth.close();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}