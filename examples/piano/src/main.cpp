#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <VSynth/VSynth.h>

#include <algorithm>
#include <map>
#include <vector>
#include <iostream>

using namespace VSynth;
using namespace Generators;

struct PianoKey
{
    char key;
    double frequency;
};

// Keyboard to Piano Notes
// First item is the keyboard key, second item is the note to play
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

void renderKeyBindings(SDL_Window *window);

void initSDL();

SDL_Window *createWindow();

int main(int argc, char *argv[])
{
    // Init SDL and create Window
    initSDL();
    SDL_Window *window = createWindow();
    renderKeyBindings(window);

    /**
     * Create an instrument with the Piano
     * patch and envelope.
     * VSynth provides some patches and
     * envelopes within Patches.h.
     * You can write your own as well.
     */
    Instrument *piano = new PolyphonicInstrument(
        Patches::PIANO,
        Patches::PIANO_ENVELOPE);

    // Creating a synthesizer
    Synthesizer synth;

    // Add our instrument to the synth
    synth.addSoundGenerator(piano);

    // Open the synth for playback
    synth.open();
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
                                // Hold note plays the given note (frequency)
                                piano->holdNote(it->frequency);
                                pressedKeys[it->key] = true;
                            }
                        }
                        else if (e.type == SDL_KEYUP)
                        {
                            // Release note stops the given note (frequency)
                            piano->releaseNote(it->frequency);
                            pressedKeys[it->key] = false;
                        }
                    }
                }
            }
        }
    }

    // Cleanup
    synth.pause();
    synth.close();

    // Exit SDL
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

void renderKeyBindings(SDL_Window *window)
{
    SDL_Surface *windowSurface = SDL_GetWindowSurface(window);
    SDL_Surface *keyBindImage = IMG_Load("assets/KeyMap.png");

    // Scale Image to fit screen better
    double scaleWidth = (double)windowSurface->w / (double)keyBindImage->w;
    double scaleHeight = (double)windowSurface->h / (double)keyBindImage->h;
    double scale = std::min(scaleHeight, scaleWidth);

    SDL_Rect dest = {(windowSurface->w - (keyBindImage->w * scale)) / 2,
                     (windowSurface->h - (keyBindImage->h * scale)) / 2,
                     (double)keyBindImage->w * scale,
                     (double)keyBindImage->h * scale};

    // Scaled rendering
    SDL_BlitScaled(keyBindImage, nullptr, windowSurface, &dest);
    SDL_UpdateWindowSurface(window);

    // Free Key Bind Image
    SDL_FreeSurface(keyBindImage);
}

void initSDL()
{
    // SDL initialization
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
}

SDL_Window *createWindow()
{
    return SDL_CreateWindow("Piano Example",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            1600,
                            900,
                            SDL_WINDOW_SHOWN);
}