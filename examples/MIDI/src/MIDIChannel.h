#pragma once

#include <VSynth/SoundGenerator.h>
#include <VSynth/utils/Envelope.h>

#include <functional>
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

class MIDIChannel: public VSynth::SoundGenerator
{

public:
    MIDIChannel(
        const std::function<double(double, double)> patch,
        const VSynth::ADSREnvelope adsr
        );
    ~MIDIChannel();

    double sample(double time);

    void handleEvent(const MIDI_EVENT &event);

private:

    struct NoteData {
        bool on;
        uint8_t velocity;
        VSynth::Envelope env;
    };

    double mPrevSample;
    
    std::function<double(double, double)> mPatch;
    std::vector<NoteData> mNotes;
};