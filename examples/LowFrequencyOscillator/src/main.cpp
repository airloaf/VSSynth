#include <SDL2/SDL.h>

#include <VSynth/VSynth.h>

using namespace VSynth;
using namespace Generators;

void initSDL();
SDL_Window *createWindow();

int main(int argc, char *argv[])
{
    // SDL initialization
    initSDL();
    SDL_Window *window = createWindow();

    // Create a Low frequency oscillator
    Tone tone(
        [](double frequency, double time) {
            return Waveforms::sawtooth(
                frequency,
                time,
                0.01 * frequency * Waveforms::sine(5, time)); // LFO
        });
    tone.playNote(Notes::C4);

    // Create a synthesizer, with default settings
    Synthesizer synth;

    // Open the synth for playback with the sine wave we have created
    synth.open();
    synth.addSoundGenerator(&tone);
    synth.unpause();

    // Wait until user closes window
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
        }
    }

    // Prior to destroying the synth, it is good
    // practice to pause the synth first!
    synth.pause();
    synth.close();

    // SDL de-initialization
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void initSDL()
{
    // SDL initialization
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
}

SDL_Window *createWindow()
{
    return SDL_CreateWindow("Simple Tone Example",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            1600,
                            900,
                            SDL_WINDOW_SHOWN);
}