#pragma once

#include <cstdint>
#include <vector>

#include "MIDIChannel.h"

class MIDISequencer : public VSSynth::SoundGenerator
{
public:
    MIDISequencer(MIDIChannel *channel);
    ~MIDISequencer();

    double sample(double time);

    void addNotePlayEvent(uint8_t note, uint8_t velocity, double startTime, double duration);
    void addNotePressureEvent(uint8_t note, uint8_t pressure, double startTime);
    void addControllerEvent(uint8_t controller, uint8_t value, double startTime);
    void addProgramChangeEvent(uint8_t program, double startTime);
    void addPitchBendEvent(uint8_t lsb, uint8_t msb, double startTime);

    void sortEventsByTime();

private:
    MIDIChannel *mChannel;

    double mStartTime;
    double mCurTime;

    std::vector<std::pair<MIDI_EVENT, double>> mEvents;
    std::vector<std::pair<MIDI_EVENT, double>>::iterator mEventIt;
};