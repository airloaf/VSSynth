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

    // Creates a Sine wave at "Middle C"
    Tone tone(
        [](double frequency, double time) {
            return Waveforms::sine(frequency, time);
        });
    tone.playNote(Notes::C4);

    // Create a WAVWriter to save the waveform
    VSynth::Middleware::WAVWriter wavWriter(48000);
    wavWriter.open("tone.wav");

    // Create synthesizer
    Synthesizer synth;

    // Add WAVWriter to the synthesizer
    synth.addMiddleware(&wavWriter);

    // Add our tone to the sound generator 
    synth.addSoundGenerator(&tone);

    // Open the synth for playback with the
    // sine wave we have created
    synth.open();
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

    // Close the wave file to save it
    wavWriter.close();

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
    return SDL_CreateWindow("Record Tone Example",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            1600,
                            900,
                            SDL_WINDOW_SHOWN);
}