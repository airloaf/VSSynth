#include "MIDISequencer.h"

#include <algorithm>

MIDISequencer::MIDISequencer(MIDIChannel *channel)
    : mChannel(channel),
      mStartTime(0),
      mCurTime(0)
{
}

MIDISequencer::~MIDISequencer()
{
}

double MIDISequencer::sample(double time)
{
    mCurTime = time;

    // Play all notes ready to be enqueued
    while (
        mEventIt != mEvents.end() &&
        (mEventIt->second < (mCurTime - mStartTime)))
    {
        mChannel->handleEvent(mEventIt->first);
        mEventIt++;
    }

    return mChannel->sample(time);
}

void MIDISequencer::addNotePlayEvent(uint8_t note, uint8_t velocity, double startTime, double duration)
{
    MIDI_EVENT noteOn, noteOff;

    noteOn.type = MIDI_EVENT_TYPE::NOTE_ON;
    noteOn.note = note;
    noteOn.velocity = velocity;

    noteOff.type = MIDI_EVENT_TYPE::NOTE_OFF;
    noteOff.note = note;
    noteOff.velocity = velocity;

    mEvents.push_back({noteOn, startTime});
    mEvents.push_back({noteOff, startTime + duration});
}

void MIDISequencer::addNotePressureEvent(uint8_t note, uint8_t pressure, double startTime)
{
    MIDI_EVENT notePressure;

    notePressure.type = MIDI_EVENT_TYPE::NOTE_AFTERTOUCH;
    notePressure.note = note;
    notePressure.note_pressure = pressure;

    mEvents.push_back({notePressure, startTime});
}

void MIDISequencer::addControllerEvent(uint8_t controller, uint8_t value, double startTime)
{
    MIDI_EVENT controllerEvent;

    controllerEvent.type = MIDI_EVENT_TYPE::CONTROLLER;
    controllerEvent.controller = controller;
    controllerEvent.value = value;

    mEvents.push_back({controllerEvent, startTime});
}

void MIDISequencer::addProgramChangeEvent(uint8_t program, double startTime)
{
    MIDI_EVENT programChange;

    programChange.type = MIDI_EVENT_TYPE::PROGRAM_CHANGE;
    programChange.program = program;

    mEvents.push_back({programChange, startTime});
}

void MIDISequencer::addPitchBendEvent(uint8_t lsb, uint8_t msb, double startTime)
{

    MIDI_EVENT pitchBendEvent;

    pitchBendEvent.type = MIDI_EVENT_TYPE::PITCH_BEND;
    pitchBendEvent.bendLSB = lsb;
    pitchBendEvent.bendMSB = msb;

    mEvents.push_back({pitchBendEvent, startTime});
}

void MIDISequencer::sortEventsByTime()
{
    std::sort(
        mEvents.begin(),
        mEvents.end(),
        [](const auto &rhs, const auto &lhs) {
            return rhs.second < lhs.second;
        });

    mEventIt = mEvents.begin();
}