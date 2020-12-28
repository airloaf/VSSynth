#include <Midifile/MidiFile.h>

#include <SDL2/SDL.h>

#include <VSynth/Generators/PolyphonicInstrument.h>
#include <VSynth/Generators/Sequencer.h>
#include <VSynth/Synthesizer.h>
#include <VSynth/utils/Envelope.h>

#include <iostream>

int main(int argc, char *argv[]){
    smf::MidiFile midifile;
    midifile.read("../../midis/tmnt400.mid");

    midifile.doTimeAnalysis();
    midifile.linkNotePairs();

    int tracks = midifile.getTrackCount();
    std::cout << "Number of Tracks: " << tracks << std::endl;

    std::cout << "Ticks Per Quarter Note: " << midifile.getTicksPerQuarterNote() << std::endl;

    for(int track = 0; track < tracks; track++){
        std::cout << "Track " << track << std::endl;
        std::cout << "Seconds\tMessage" << std::endl;
        for(int event = 0; event < midifile[track].size(); event++){
            if(midifile[track][event].isNote()){
                std::cout << std::dec << midifile[track][event].seconds;
                std::cout << '\t' << midifile[track][event].getDurationInSeconds();
                std::cout << '\t' << std::hex;
                for (int i=0; i<midifile[track][event].size(); i++)
                    std::cout << (int)midifile[track][event][i] << ' ';
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}