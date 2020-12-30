#include "MIDIChannel.h"
#include "MIDIPatches.h"

#define VELCOCITY_MAX 127.0

MIDIChannel::MIDIChannel(std::function<double(double, double)> patch)
    : mPatch(patch), mNotes(128, {false, 0})
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
    for (int i = 0; i < 128; i++)
    {
        if (mNotes[i].on)
        {
            sample += mPatch(noteToFreq(i), time) *
                      (((double)mNotes[i].velocity) / VELCOCITY_MAX);
        }
    }
    return sample;
}

void MIDIChannel::handleEvent(const MIDI_EVENT &event)
{
    if (event.type == MIDI_EVENT_TYPE::NOTE_ON)
    {
        mNotes[event.note].on = true;
        mNotes[event.note].velocity = event.velocity;
    }
    else if (event.type == MIDI_EVENT_TYPE::NOTE_OFF)
    {
        mNotes[event.note].on = false;
        mNotes[event.note].velocity = event.velocity;
    }
    else if(event.type == MIDI_EVENT_TYPE::PROGRAM_CHANGE){
        mPatch = PATCHES[event.program];
    }
}