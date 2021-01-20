#include <SDL2/SDL.h>

#include <VSSynth/VSSynth.h>

using namespace VSSynth;
using namespace Generators;

void initSDL();
SDL_Window *createWindow();

int main(int argc, char *argv[])
{
    // SDL initialization
    // SDL has to be initialized with SDL_INIT_AUDIO
    // otherwise the synthesizer will not work!
    initSDL();
    SDL_Window *window = createWindow();

    // Creates a Sine wave at "Middle C"
    // In this example we create the sine wave in-line,
    // there are synth patches available with the library
    // that produce richer noises than just a sine wave.
    // See the Patches.h file within utils
    Tone tone(
        [](double frequency, double time) {
            return Waveforms::sine(frequency, time);
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