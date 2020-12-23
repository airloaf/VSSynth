#include <VSynth/Synthesizer.h>
#include <Midifile/MidiFile.h>

#include <iostream>

std::string parseMidiMessage(const smf::MidiEvent &event);

int main(int argc, char *argv[]){
    smf::MidiFile midifile;
    midifile.read("../../midis/tmnt400.mid");

    midifile.doTimeAnalysis();

    int tracks = midifile.getTrackCount();
    std::cout << "Number of Tracks: " << tracks << std::endl;

    std::cout << "Ticks Per Quarter Note: " << midifile.getTicksPerQuarterNote() << std::endl;

    for(int track = 0; track < tracks; track++){
        std::cout << "Track " << track << std::endl;
        std::cout << "Seconds\tMessage" << std::endl;
        for(int event = 0; event < midifile[track].size(); event++){
            std::cout << std::dec << midifile[track][event].seconds;
            std::cout << '\t' << std::hex;
            for (int i=0; i<midifile[track][event].size(); i++)
                std::cout << (int)midifile[track][event][i] << ' ';
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}

std::string parseMidiMessage(const smf::MidiEvent &event){
    std::string ret = "";

    if(event.isNoteOff()){
        ret = "Setting Note " + event.getP1();
        ret += " off ";
    }else if(event.isNoteOn()){
        ret = "Setting Note " + event.getP1();
        ret += " on ";
    }else if(event.isAftertouch()){
        ret = "Setting Note " + event.getP1();
        ret += " on ";
    }else if(event.isController()){

    }else if(event.isTimbre()){

    }else if(event.isPressure()){

    }else if(event.isPitchbend()){

    }

    return ret;
}