#include <Midifile/MidiFile.h>

#include <SDL2/SDL.h>

#include <VSynth/Generators/PolyphonicInstrument.h>
#include <VSynth/Generators/Sequencer.h>
#include <VSynth/Synthesizer.h>
#include <VSynth/utils/Envelope.h>
#include <VSynth/utils/Patches.h>

#include <algorithm>
#include <vector>

#include <iostream>

double noteToFrequency(int midiNote)
{
    return 440.0 * pow(2.0, ((double)midiNote - 69.0) / 12.0);
}

void addNotesToSequencer(std::vector<VSynth::Sequencer> &seqs, smf::MidiFile &file)
{
    int tracks = file.getTrackCount();
    std::cout << "Number of Tracks: " << tracks << std::endl;

    std::cout << "Ticks Per Quarter Note: " << file.getTicksPerQuarterNote() << std::endl;

    for (int track = 0; track < tracks; track++)
    {
        std::cout << "Track " << track << std::endl;
        std::cout << "Seconds\tMessage" << std::endl;
        for (int event = 0; event < file[track].size(); event++)
        {
            if (file[track][event].isNoteOn())
            {
                // std::cout << "Start Time: " << file[track][event].seconds << "\t";
                // std::cout << "Duration: " << file[track][event].getDurationInSeconds() << "\t";
                // std::cout << "Note: " << std::hex << file[track][event].getP1() << std::dec << std::endl;

                double note = noteToFrequency(file[track][event].getP1());
                double startTime = file[track][event].seconds;
                double duration = file[track][event].getDurationInSeconds();

                seqs[file[track][event].getChannelNibble()].queueNote(note, startTime, duration);
                // std::cout << std::dec << file[track][event].seconds;
                // std::cout << '\t' << file[track][event].getDurationInSeconds();
                // std::cout << '\t' << std::hex;
                // for (int i = 0; i < file[track][event].size(); i++)
                //     std::cout << (int)file[track][event][i] << ' ';
                // std::cout << std::endl;
            }
        }
        std::cout << std::endl;
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
    VSynth::ADSREnvelope pianoEnvelope(0.90f, 0.30f, 0.01f, 0.01f, 0.01f);
    VSynth::Instrument *piano = new VSynth::PolyphonicInstrument(
        VSynth::Patches::PIANO,
        pianoEnvelope);

    std::vector<VSynth::Sequencer> seqs;

    for (int i = 0; i < 16; i++)
    {
        // Create a sequencer for the beat
        VSynth::Sequencer seq(new VSynth::PolyphonicInstrument(
            VSynth::Patches::PIANO,
            pianoEnvelope));
        seq.setVolume(50);
        seqs.push_back(seq);
    }

    addNotesToSequencer(seqs, midifile);

    VSynth::Synthesizer synth(30000, 2);
    synth.open();
    for(auto it = seqs.begin(); it != seqs.end(); it++){
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