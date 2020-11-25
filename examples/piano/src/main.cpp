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


        double freqToRad(double frequency)
        {
            return frequency * 2.0 * 3.1415926535;
        }

void createInstruments(Synthesizer &synth)
{

    std::function<double(double)> wave =
    std::bind(
        Waveforms::sine,
        5,
        std::placeholders::_1);

    for (auto it = pianoKeys.begin(); it != pianoKeys.end(); it++)
    {
        Instrument instrument;
        instrument.amplitude = 3000;
        instrument.envelope = &it->env;
        instrument.wave = std::bind(
            Waveforms::modulatedWave,
            Waveforms::triangle,
            it->frequency,
            0.01,
            wave,
            std::placeholders::_1);
        synth.addInstrument(instrument);
    }
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
                            it->env.hold();
                        }
                        else if (e.type == SDL_KEYUP)
                        {
                            it->env.release();
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