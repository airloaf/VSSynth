#include <SDL2/SDL.h>
#include <vector>

#include <VSynth/Envelope.h>
#include <VSynth/Synthesizer.h>
#include <VSynth/Waveforms.h>
#include <VSynth/Generators/PolyphonicInstrument.h>
#include <VSynth/Generators/MonophonicInstrument.h>

using namespace VSynth;

struct PianoKey
{
    char key;
    double frequency;
};

std::vector<PianoKey> pianoKeys = {
    {SDLK_a, 262},
    {SDLK_s, 294},
    {SDLK_d, 330},
    {SDLK_f, 350},
    {SDLK_g, 392},
    {SDLK_h, 440},
    {SDLK_j, 494},
    {SDLK_k, 523}};

Instrument *createInstrument()
{
    return new MonophonicInstrument(
        [](double freq, double time) {
            return 0.5 * (Waveforms::sine(freq, time) +
                          0.5 * Waveforms::sine(freq * 2, time) +
                          0.25 * Waveforms::sine(freq * 3, time) +
                          0.125 * Waveforms::sine(freq * 4, time) +
                          0.0625 * Waveforms::sine(freq * 5, time) +
                          0.03125 * Waveforms::sine(freq * 6, time) +
                          0.015625 * Waveforms::sine(freq * 7, time));
        },
        ADSREnvelope(0.90f, 0.60f, 0.20f, 0.20f, 0.50f)
        );
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window *window;
    window = SDL_CreateWindow("SDL_Test_Windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    Instrument *piano = createInstrument();

    Synthesizer synth;
    synth.open();
    synth.addSoundGenerator(piano);
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
                            piano->holdNote(it->frequency);
                        }
                        else if (e.type == SDL_KEYUP)
                        {
                            piano->releaseNote(it->frequency);
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