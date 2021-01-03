#include <SDL2/SDL.h>

#include <VSynth/Synthesizer.h>
#include <VSynth/generators/Tone.h>
#include <VSynth/middleware/WAVWriter.h>
#include <VSynth/utils/Notes.h>
#include <VSynth/utils/Waveforms.h>

using namespace VSynth;

int main(int argc, char *argv[])
{
    // SDL initialization
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    SDL_Window *window;
    window = SDL_CreateWindow("Simple Tone Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 450, SDL_WINDOW_SHOWN);

    // Creates a Sine wave at "Middle C"
    Tone tone(
        [](double frequency, double time) {
            return Waveforms::sine(frequency, time);
        });
    tone.playNote(Notes::C4);

    // Create a synthesizer at 48 KHz
    Synthesizer synth(48000);

    // Create a WAVWriter to save the waveform
    VSynth::Middleware::WAVWriter wavWriter(48000);
    wavWriter.open("tone.wav");

    // Add WAVWriter to the synthesizer
    synth.addMiddleware(&wavWriter);

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

    // Close the wave file to save it
    wavWriter.close();

    // SDL de-initialization
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}