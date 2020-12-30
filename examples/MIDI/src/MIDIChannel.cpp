#include "MIDIChannel.h"

MIDIChannel::MIDIChannel(std::function<double(double, double)> patch)
    : mPatch(patch), mNotes(128, false)
{
}

MIDIChannel::~MIDIChannel()
{
}

// Converts MIDI notes to a frequency in hertz
double noteToFreq(int midiNote)
{
    return 440.0 * pow(2.0, ((double)midiNote - 69.0) / 12.0);
}

double MIDIChannel::sample(double time)
{
    double sample = 0.0;
    for(int i = 0; i < 128; i++){
        if(mNotes[i]){
            sample += mPatch(noteToFreq(i), time);
        }
    }
    return sample;
}

void MIDIChannel::handleEvent(const MIDI_EVENT &event)
{
    if(event.type == MIDI_EVENT_TYPE::NOTE_ON){
        mNotes[event.note] = true;
    }else if(event.type == MIDI_EVENT_TYPE::NOTE_OFF){
        mNotes[event.note] = false;
    }
}