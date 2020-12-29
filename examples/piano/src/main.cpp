#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <VSynth/Synthesizer.h>
#include <VSynth/generators/MonophonicInstrument.h>
#include <VSynth/generators/PolyphonicInstrument.h>
#include <VSynth/utils/Envelope.h>
#include <VSynth/utils/Notes.h>
#include <VSynth/utils/Patches.h>
#include <VSynth/utils/Waveforms.h>

#include <map>
#include <vector>

using namespace VSynth;

struct PianoKey
{
    char key;
    double frequency;
};

// Keyboard to Piano Notes
std::vector<PianoKey> pianoKeys = {
    {SDLK_a, Notes::C4},
    {SDLK_w, Notes::Cs4},
    {SDLK_s, Notes::D4},
    {SDLK_e, Notes::Ds4},
    {SDLK_d, Notes::E4},
    {SDLK_f, Notes::F4},
    {SDLK_t, Notes::Fs4},
    {SDLK_g, Notes::G4},
    {SDLK_y, Notes::Gs4},
    {SDLK_h, Notes::A4},
    {SDLK_u, Notes::As4},
    {SDLK_j, Notes::B4},
    {SDLK_k, Notes::C5},
    {SDLK_o, Notes::Cs5},
    {SDLK_l, Notes::D5},
    {SDLK_p, Notes::Ds5},
    {SDLK_SEMICOLON, Notes::E5}};

int main(int argc, char *argv[])
{
    // SDL initialization
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    // Create SDL Window to grab keyboard input
    SDL_Window *window;
    window = SDL_CreateWindow("Piano Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);
    SDL_Surface *windowSurface = SDL_GetWindowSurface(window);

    // Render Keybindings to screen
    SDL_Surface *keyBindImage = IMG_Load("assets/KeyMap.png");
    SDL_BlitSurface(keyBindImage, nullptr, windowSurface, nullptr);
    SDL_UpdateWindowSurface(window);

    // Create an instrument with the following envelope and patch
    ADSREnvelope pianoEnvelope(1.00f, 0.50f, 0.10f, 0.10f, 0.50f);
    Instrument *piano = new MonophonicInstrument(
        Patches::BRASS,
        pianoEnvelope);

    // Creating a synthesizer
    Synthesizer synth;
    synth.open();
    synth.addSoundGenerator(piano);
    synth.unpause();

    // Keep track of pressed keys, this is important since the
    // SDL_KEYDOWN event will keep emitting as long as the key is held
    std::map<char, bool> pressedKeys;

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
                // Check which keys are being pressed and play the appropriate note
                for (auto it = pianoKeys.begin(); it != pianoKeys.end(); it++)
                {
                    if (e.key.keysym.sym == it->key)
                    {
                        if (e.type == SDL_KEYDOWN)
                        {
                            if (!pressedKeys[it->key])
                            {
                                piano->holdNote(it->frequency);
                                pressedKeys[it->key] = true;
                            }
                        }
                        else if (e.type == SDL_KEYUP)
                        {
                            pressedKeys[it->key] = false;
                            piano->releaseNote(it->frequency);
                        }
                    }
                }
            }
        }
    }

    // Cleanup
    synth.pause();
    synth.close();

    SDL_FreeSurface(keyBindImage);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}