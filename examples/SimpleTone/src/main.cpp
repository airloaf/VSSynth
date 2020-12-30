#include <SDL2/SDL.h>

#include <VSynth/Generators/Tone.h>
#include <VSynth/Synthesizer.h>
#include <VSynth/utils/Notes.h>
#include <VSynth/utils/Waveforms.h>

using namespace VSynth;

int main(int argc, char *argv[])
{
    // SDL initialization
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    SDL_Window *window;
    window = SDL_CreateWindow("Simple Tone Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 450, SDL_WINDOW_SHOWN);

    // Create a Sine wave at "Middle C"
    Tone tone(
        [](double frequency, double time) {
            return Waveforms::sine(frequency, time);
        });
    tone.playNote(Notes::C4);

    // Creating a synthesizer
    Synthesizer synth;
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
    synth.pause();
    synth.close();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}