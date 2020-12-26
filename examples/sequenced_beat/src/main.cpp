#include <SDL2/SDL.h>

#include <VSynth/Synthesizer.h>
#include <VSynth/generators/MonophonicInstrument.h>
#include <VSynth/generators/PolyphonicInstrument.h>
#include <VSynth/generators/Sequencer.h>
#include <VSynth/utils/Envelope.h>
#include <VSynth/utils/Notes.h>
#include <VSynth/utils/Patches.h>

#include <map>
#include <vector>

using namespace VSynth;

struct PianoKey
{
    char key;
    double frequency;
};

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
    {SDLK_l, Notes::D5},
    {SDLK_SEMICOLON, Notes::E5}};

void setSequencerBeat(Sequencer &seq){
    seq.addNoteEvent({Notes::A4, true}, 1.0);
    seq.addNoteEvent({Notes::A4, false}, 2.0);
    seq.addNoteEvent({Notes::As4, true}, 2.0);
    seq.addNoteEvent({Notes::As4, false}, 3.0);
    seq.addNoteEvent({Notes::B4, true}, 3.0);
    seq.addNoteEvent({Notes::B4, false}, 4.0);
    seq.addNoteEvent({Notes::E5, true}, 4.0);
    seq.addNoteEvent({Notes::E5, false}, 5.0);
}

int main(int argc, char *argv[])
{
    // SDL initialization
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    // Create SDL Window to grab keyboard input
    SDL_Window *window;
    window = SDL_CreateWindow("Piano Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    // Create an instrument with the following envelope and patch
    ADSREnvelope pianoEnvelope(0.90f, 0.60f, 0.20f, 0.20f, 0.50f);
    Instrument *piano = new PolyphonicInstrument(
        Patches::PIANO,
        pianoEnvelope);

    // Create a sequencer for the beat
    Sequencer seq(new PolyphonicInstrument(
        Patches::ORGAN,
        pianoEnvelope));

    // Set the sequencer beat
    setSequencerBeat(seq);

    // Creating a synthesizer
    Synthesizer synth;
    synth.open();
    synth.addSoundGenerator(piano);
    synth.addSoundGenerator(&seq);
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
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}