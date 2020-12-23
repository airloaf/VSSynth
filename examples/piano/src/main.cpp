#include <SDL2/SDL.h>
#include <vector>

#include <VSynth/Envelope.h>
#include <VSynth/Synthesizer.h>
#include <VSynth/Waveforms.h>

#include <cmath>

using namespace VSynth;

ADSREnvelope pianoADSR(0.90f, 0.60f, 0.20f, 0.20f, 0.50f);

struct PianoKey
{
    char key;
    double frequency;
    Envelope env;
};

std::vector<PianoKey> pianoKeys = {
    {SDLK_a, 262, Envelope(pianoADSR)},
    {SDLK_s, 294, Envelope(pianoADSR)},
    {SDLK_d, 330, Envelope(pianoADSR)},
    {SDLK_f, 350, Envelope(pianoADSR)},
    {SDLK_g, 392, Envelope(pianoADSR)},
    {SDLK_h, 440, Envelope(pianoADSR)},
    {SDLK_j, 494, Envelope(pianoADSR)},
    {SDLK_k, 523, Envelope(pianoADSR)}
};

Instrument *wave = nullptr;

void createInstruments(Synthesizer &synth)
{

    wave = new Instrument(
        [](double freq, double time){
            return 0.5 * (
                Waveforms::sine(freq, time) +
                0.5 * Waveforms::sine(freq*2, time) +
                0.25 * Waveforms::sine(freq*3, time) +
                0.125 * Waveforms::sine(freq*4, time) +
                0.0625 * Waveforms::sine(freq*5, time) +
                0.03125 * Waveforms::sine(freq*6, time) +
                0.015625 * Waveforms::sine(freq*7, time)
            );
        },
        pianoADSR
    );

    synth.addInstrument(wave);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window *window;
    window = SDL_CreateWindow("SDL_Test_Windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    Synthesizer synth;
    synth.open();
    createInstruments(synth);
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
            else
            {
                for (auto it = pianoKeys.begin(); it != pianoKeys.end(); it++)
                {
                    if (e.key.keysym.sym == it->key)
                    {
                        if (e.type == SDL_KEYDOWN)
                        {
                            // it->env.hold();
                            wave->holdNote(it->frequency);
                        }
                        else if (e.type == SDL_KEYUP)
                        {
                            // it->env.release();
                            wave->releaseNote(it->frequency);
                        }
                    }
                }
            }
        }
    }

    synth.close();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}