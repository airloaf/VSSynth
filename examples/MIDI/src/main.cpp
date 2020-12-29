#include <Midifile/MidiFile.h>

#include <SDL2/SDL.h>

#include <VSynth/Generators/MonophonicInstrument.h>
#include <VSynth/Generators/PolyphonicInstrument.h>
#include <VSynth/Generators/Sequencer.h>
#include <VSynth/Synthesizer.h>
#include <VSynth/utils/Envelope.h>
#include <VSynth/utils/Patches.h>

#include <algorithm>
#include <vector>

double noteToFrequency(int midiNote)
{
    return 440.0 * pow(2.0, ((double)midiNote - 69.0) / 12.0);
}

void addNotesToSequencer(std::vector<VSynth::Sequencer> &seqs, smf::MidiFile &file)
{
    int tracks = file.getTrackCount();

    for (int track = 0; track < tracks; track++)
    {
        for (int event = 0; event < file[track].size(); event++)
        {
            if (file[track][event].isNoteOn())
            {
                double note = noteToFrequency(file[track][event].getP1());
                double startTime = file[track][event].seconds;
                double duration = file[track][event].getDurationInSeconds();

                seqs[file[track][event].getChannelNibble()].queueNote(note, startTime, duration);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc <= 1){
        return 0;
    }
    smf::MidiFile midifile;
    midifile.read(argv[1]);

    midifile.doTimeAnalysis();
    midifile.linkNotePairs();

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window *window;
    window = SDL_CreateWindow("MIDI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    // Create an instrument with the following envelope and patch
    std::vector<VSynth::Sequencer> seqs;

    for (int i = 0; i < 16; i++)
    {
        // Create a sequencer for the beat
        VSynth::Sequencer seq(new VSynth::PolyphonicInstrument(
            VSynth::Patches::REED,
            VSynth::Patches::REED_ENVELOPE));
        seqs.push_back(seq);
    }

    addNotesToSequencer(seqs, midifile);

    VSynth::Synthesizer synth(25000, 50);
    synth.open();
    for(auto it = seqs.begin(); it != seqs.end(); it++){
        it->sortNotes();
        synth.addSoundGenerator(&(*it));
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