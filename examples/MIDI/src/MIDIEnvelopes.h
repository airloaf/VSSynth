#pragma once

#include <VSynth/utils/Envelope.h>
#include <VSynth/utils/Patches.h>

using namespace VSynth::Patches;

// PATCH Table found at (https://en.wikipedia.org/wiki/General_MIDI#Program_change_events)

const VSynth::ADSREnvelope ENVELOPES[] = {
    PIANO_ENVELOPE,        //1 Acoustic Grand Piano
    PIANO_ENVELOPE,        //2 Bright Acoustic Piano
    PIANO_ENVELOPE,        //3 Electric Grand Piano
    PIANO_ENVELOPE,        //4 Honky-tonk Piano
    PIANO_ENVELOPE,        //5 Electric Piano 1
    PIANO_ENVELOPE,        //6 Electric Piano 2
    PIANO_ENVELOPE,        //7 Harpsichord
    PIANO_ENVELOPE,        //8 Clavi
    GLOCKENSPIEL_ENVELOPE, //9 Celesta
    GLOCKENSPIEL_ENVELOPE, //10 Glockenspiel
    GLOCKENSPIEL_ENVELOPE, //11 Music Box
    GLOCKENSPIEL_ENVELOPE, //12 Vibraphone
    GLOCKENSPIEL_ENVELOPE, //13 Marimba
    GLOCKENSPIEL_ENVELOPE, //14 Xylophone
    GLOCKENSPIEL_ENVELOPE, //15 Tubular Bells
    GLOCKENSPIEL_ENVELOPE, //16 Dulcimer
    ORGAN_ENVELOPE,        //17 Drawbar Organ
    ORGAN_ENVELOPE,        //18 Percussive Organ
    ORGAN_ENVELOPE,        //19 Rock Organ
    ORGAN_ENVELOPE,        //20 Church Organ
    ORGAN_ENVELOPE,        //21 Reed Organ
    ORGAN_ENVELOPE,        //22 Accordion
    ORGAN_ENVELOPE,        //23 Harmonica
    ORGAN_ENVELOPE,        //24 Tango Accordion
    GUITAR_ENVELOPE,       //25 Acoustic Guitar (nylon)
    GUITAR_ENVELOPE,       //26 Acoustic Guitar (steel)
    GUITAR_ENVELOPE,       //27 Electric Guitar (jazz)
    GUITAR_ENVELOPE,       //28 Electric Guitar (clean)
    GUITAR_ENVELOPE,       //29 Electric Guitar (muted)
    GUITAR_ENVELOPE,       //30 Overdriven Guitar
    GUITAR_ENVELOPE,       //31 Distortion Guitar
    GUITAR_ENVELOPE,       //32 Guitar Harmonics
    BASS_ENVELOPE,         //33 Acoustic Bass
    BASS_ENVELOPE,         //34 Electric Bass (finger)
    BASS_ENVELOPE,         //35 Electric Bass (pick)
    BASS_ENVELOPE,         //36 Fretless Bass
    BASS_ENVELOPE,         //37 Slap Bass 1
    BASS_ENVELOPE,         //38 Slap Bass 2
    BASS_ENVELOPE,         //39 Synth Bass 1
    BASS_ENVELOPE,         //40 Synth Bass 2
    PIANO_ENVELOPE,        //41 Violin
    PIANO_ENVELOPE,        //42 Viola
    PIANO_ENVELOPE,        //43 Cello
    PIANO_ENVELOPE,        //44 Contrabass
    PIANO_ENVELOPE,        //45 Tremolo Strings
    PIANO_ENVELOPE,        //46 Pizzicato Strings
    PIANO_ENVELOPE,        //47 Orchestral Harp
    PIANO_ENVELOPE,        //48 Timpani
    PIANO_ENVELOPE,        //49 String Ensemble 1
    PIANO_ENVELOPE,        //50 String Ensemble 2
    PIANO_ENVELOPE,        //51 Synth Strings 1
    PIANO_ENVELOPE,        //52 Synth Strings 2
    PIANO_ENVELOPE,        //53 Choir Aahs
    PIANO_ENVELOPE,        //54 Voice Oohs
    PIANO_ENVELOPE,        //55 Synth Voice
    PIANO_ENVELOPE,        //56 Orchestra Hit
    BRASS_ENVELOPE,        //57 Trumpet
    BRASS_ENVELOPE,        //58 Trombone
    BRASS_ENVELOPE,        //59 Tuba
    BRASS_ENVELOPE,        //60 Muted Trumpet
    BRASS_ENVELOPE,        //61 French Horn
    BRASS_ENVELOPE,        //62 Brass Section
    BRASS_ENVELOPE,        //63 Synth Brass 1
    BRASS_ENVELOPE,        //64 Synth Brass 2
    BRASS_ENVELOPE,        //65 Soprano Sax
    BRASS_ENVELOPE,        //66 Alto Sax
    BRASS_ENVELOPE,        //67 Tenor Sax
    BRASS_ENVELOPE,        //68 Baritone Sax
    BRASS_ENVELOPE,        //69 Oboe
    BRASS_ENVELOPE,        //70 English Horn
    BRASS_ENVELOPE,        //71 Bassoon
    BRASS_ENVELOPE,        //72 Clarinet
    REED_ENVELOPE,         //73 Piccolo
    REED_ENVELOPE,         //74 Flute
    REED_ENVELOPE,         //75 Recorder
    REED_ENVELOPE,         //76 Pan Flute
    REED_ENVELOPE,         //77 Blown bottle
    REED_ENVELOPE,         //78 Shakuhachi
    REED_ENVELOPE,         //79 Whistle
    REED_ENVELOPE,         //80 Ocarina
    PIANO_ENVELOPE,        //81 Lead 1 (square)
    PIANO_ENVELOPE,        //82 Lead 2 (sawtooth)
    PIANO_ENVELOPE,        //83 Lead 3 (calliope)
    PIANO_ENVELOPE,        //84 Lead 4 (chiff)
    PIANO_ENVELOPE,        //85 Lead 5 (charang)
    PIANO_ENVELOPE,        //86 Lead 6 (voice)
    PIANO_ENVELOPE,        //87 Lead 7 (fifths)
    PIANO_ENVELOPE,        //88 Lead 8 (bass + lead)
    PIANO_ENVELOPE,        //89 Pad 1 (new age)
    PIANO_ENVELOPE,        //90 Pad 2 (warm)
    PIANO_ENVELOPE,        //91 Pad 3 (polysynth)
    PIANO_ENVELOPE,        //92 Pad 4 (choir)
    PIANO_ENVELOPE,        //93 Pad 5 (bowed)
    PIANO_ENVELOPE,        //94 Pad 6 (metallic)
    PIANO_ENVELOPE,        //95 Pad 7 (halo)
    PIANO_ENVELOPE,        //96 Pad 8 (sweep)
    PIANO_ENVELOPE,        //97 FX 1 (rain)
    PIANO_ENVELOPE,        //98 FX 2 (soundtrack)
    PIANO_ENVELOPE,        //99 FX 3 (crystal)
    PIANO_ENVELOPE,        //100 FX 4 (atmosphere)
    PIANO_ENVELOPE,        //101 FX 5 (brightness)
    PIANO_ENVELOPE,        //102 FX 6 (goblins)
    PIANO_ENVELOPE,        //103 FX 7 (echoes)
    PIANO_ENVELOPE,        //104 FX 8 (sci-fi)
    PIANO_ENVELOPE,        //105 Sitar
    PIANO_ENVELOPE,        //106 Banjo
    PIANO_ENVELOPE,        //107 Shamisen
    PIANO_ENVELOPE,        //108 Koto
    PIANO_ENVELOPE,        //109 Kalimba
    PIANO_ENVELOPE,        //110 Bag pipe
    PIANO_ENVELOPE,        //111 Fiddle
    PIANO_ENVELOPE,        //112 Shanai
    PIANO_ENVELOPE,        //113 Tinkle Bell
    PIANO_ENVELOPE,        //114 Agogô
    PIANO_ENVELOPE,        //115 Steel Drums
    PIANO_ENVELOPE,        //116 Woodblock
    PIANO_ENVELOPE,        //117 Taiko Drum
    PIANO_ENVELOPE,        //118 Melodic Tom
    PIANO_ENVELOPE,        //119 Synth Drum
    PIANO_ENVELOPE,        //120 Reverse Cymbal
    PIANO_ENVELOPE,        //121 Guitar Fret Noise
    PIANO_ENVELOPE,        //122 Breath Noise
    PIANO_ENVELOPE,        //123 Seashore
    PIANO_ENVELOPE,        //124 Bird Tweet
    PIANO_ENVELOPE,        //125 Telephone Ring
    PIANO_ENVELOPE,        //126 Helicopter
    PIANO_ENVELOPE,        //127 Applause
    PIANO_ENVELOPE         //128 Gunshot
};