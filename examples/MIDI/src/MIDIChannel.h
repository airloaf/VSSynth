#pragma once

#include <VSSynth/SoundGenerator.h>
#include <VSSynth/utils/Envelope.h>

#include <functional>
#include <stdint.h>
#include <vector>


enum MIDI_EVENT_TYPE
{
    NOTE_ON,
    NOTE_OFF,
    NOTE_AFTERTOUCH,
    CONTROLLER,
    PROGRAM_CHANGE,
    CHANNEL_AFTERTOUCH,
    PITCH_BEND
};

struct MIDI_EVENT
{

    MIDI_EVENT_TYPE type;
    union
    {
        uint8_t note;
        uint8_t controller;
        uint8_t program;
        uint8_t channel_pressure;
        uint8_t bendLSB;
    };
    union
    {
        uint8_t velocity;
        uint8_t note_pressure;
        uint8_t value;
        uint8_t bendMSB;
    };
};

class MIDIChannel: public VSSynth::SoundGenerator
{

public:
    MIDIChannel(
        const std::function<double(double, double)> patch,
        const VSSynth::ADSREnvelope adsr
        );
    ~MIDIChannel();

    double sample(double time);

    void handleEvent(const MIDI_EVENT &event);

private:

    struct NoteData {
        bool on;
        uint8_t velocity;
        VSSynth::Envelope env;
    };

    double mPrevSample;
    
    std::function<double(double, double)> mPatch;
    std::vector<NoteData> mNotes;
};