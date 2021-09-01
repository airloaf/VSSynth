#include "MIDIChannel.h"
#include "MIDIEnvelopes.h"
#include "MIDIPatches.h"

#include <cmath>

#define VELCOCITY_MAX 127.0

MIDIChannel::MIDIChannel(
    const std::function<double(double, double)> patch,
    const VSSynth::ADSREnvelope adsr)
    : mPatch(patch), mNotes(128, {false, 0, VSSynth::ADSREnvelope(adsr)}), mPrevSample(0)
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
    double delta = time - mPrevSample;
    mPrevSample = time;

    double sample = 0.0;
    for (int i = 0; i < 128; i++)
    {
        if (mNotes[i].on)
        {
            mNotes[i].env.update(delta);
            sample += mPatch(noteToFreq(i), time) *
                      (((double)mNotes[i].velocity) / VELCOCITY_MAX) *
                      mNotes[i].env.getAmplitude();
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
        mNotes[event.note].env.hold();
    }
    else if (event.type == MIDI_EVENT_TYPE::NOTE_OFF)
    {
        mNotes[event.note].on = false;
        mNotes[event.note].velocity = event.velocity;
        mNotes[event.note].env.release();
    }
    else if (event.type == MIDI_EVENT_TYPE::PROGRAM_CHANGE)
    {
        mPatch = PATCHES[event.program];
        for(auto it = mNotes.begin(); it != mNotes.end(); it++){
            it->env.setADSR(ENVELOPES[event.program]);
        }
    }
}