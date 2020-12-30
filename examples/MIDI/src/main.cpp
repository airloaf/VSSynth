#include <Midifile/MidiFile.h>

#include <SDL2/SDL.h>

#include <VSynth/Synthesizer.h>
#include <VSynth/utils/Envelope.h>
#include <VSynth/utils/Patches.h>

#include "MIDIPatches.h"
#include "MIDISequencer.h"

#include <algorithm>
#include <vector>

void addNotesToSequencer(std::vector<MIDISequencer> &seqs, smf::MidiFile &file)
{
    int tracks = file.getTrackCount();

    for (int track = 0; track < tracks; track++)
    {
        for (int event = 0; event < file[track].size(); event++)
        {
            double startTime = file[track][event].seconds;
            int channel = file[track][event].getChannelNibble();

            smf::MidiEvent midiEvent = file[track][event];

            if (midiEvent.isNoteOn())
            {
                double duration = file[track][event].getDurationInSeconds();
                int note = file[track][event].getP1();
                int velocity = file[track][event].getP2();

                seqs[channel].addNotePlayEvent(note, velocity, startTime, duration);
            }
            else if (midiEvent.isPatchChange())
            {
                int patch = file[track][event].getP1();

                seqs[channel].addProgramChangeEvent(patch, startTime);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    smf::MidiFile midifile;
    if (argc <= 1)
    {
        midifile.read("../../midis/Take-Five-1.mid");
    }
    else
    {
        midifile.read(argv[1]);
    }

    midifile.doTimeAnalysis();
    midifile.linkNotePairs();

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window *window;
    window = SDL_CreateWindow("MIDI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    std::vector<MIDISequencer> sequencers;
    for (int i = 0; i < 16; i++)
    {
        MIDISequencer seq(new MIDIChannel(
            VSynth::Patches::GLOCKENSPIEL,
            VSynth::Patches::GLOCKENSPIEL_ENVELOPE
            ));
        sequencers.push_back(seq);
    }

    addNotesToSequencer(sequencers, midifile);

    VSynth::Synthesizer synth(25000, 50);
    synth.open();
    for (int i = 0; i < 16; i++)
    {
        sequencers[i].setVolume(50);
        sequencers[i].sortEventsByTime();
        synth.addSoundGenerator(&sequencers[i]);
    }
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
        }
    }

    synth.pause();
    synth.close();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}