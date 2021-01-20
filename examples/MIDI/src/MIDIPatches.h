#pragma once

#include <VSSynth/utils/Patches.h>

using namespace VSSynth::Patches;

// PATCH Table found at (https://en.wikipedia.org/wiki/General_MIDI#Program_change_events)

const VSSynth::Patches::Patch PATCHES[] = {
    PIANO,        //1 Acoustic Grand Piano
    PIANO,        //2 Bright Acoustic Piano
    PIANO,        //3 Electric Grand Piano
    PIANO,        //4 Honky-tonk Piano
    PIANO,        //5 Electric Piano 1
    PIANO,        //6 Electric Piano 2
    PIANO,        //7 Harpsichord
    PIANO,        //8 Clavi
    GLOCKENSPIEL, //9 Celesta
    GLOCKENSPIEL, //10 Glockenspiel
    GLOCKENSPIEL, //11 Music Box
    GLOCKENSPIEL, //12 Vibraphone
    GLOCKENSPIEL, //13 Marimba
    GLOCKENSPIEL, //14 Xylophone
    GLOCKENSPIEL, //15 Tubular Bells
    GLOCKENSPIEL, //16 Dulcimer
    ORGAN,        //17 Drawbar Organ
    ORGAN,        //18 Percussive Organ
    ORGAN,        //19 Rock Organ
    ORGAN,        //20 Church Organ
    ORGAN,        //21 Reed Organ
    ORGAN,        //22 Accordion
    ORGAN,        //23 Harmonica
    ORGAN,        //24 Tango Accordion
    GUITAR,       //25 Acoustic Guitar (nylon)
    GUITAR,       //26 Acoustic Guitar (steel)
    GUITAR,       //27 Electric Guitar (jazz)
    GUITAR,       //28 Electric Guitar (clean)
    GUITAR,       //29 Electric Guitar (muted)
    GUITAR,       //30 Overdriven Guitar
    GUITAR,       //31 Distortion Guitar
    GUITAR,       //32 Guitar Harmonics
    BASS,         //33 Acoustic Bass
    BASS,         //34 Electric Bass (finger)
    BASS,         //35 Electric Bass (pick)
    BASS,         //36 Fretless Bass
    BASS,         //37 Slap Bass 1
    BASS,         //38 Slap Bass 2
    BASS,         //39 Synth Bass 1
    BASS,         //40 Synth Bass 2
    PIANO,        //41 Violin
    PIANO,        //42 Viola
    PIANO,        //43 Cello
    PIANO,        //44 Contrabass
    PIANO,        //45 Tremolo Strings
    PIANO,        //46 Pizzicato Strings
    PIANO,        //47 Orchestral Harp
    PIANO,        //48 Timpani
    PIANO,        //49 String Ensemble 1
    PIANO,        //50 String Ensemble 2
    PIANO,        //51 Synth Strings 1
    PIANO,        //52 Synth Strings 2
    PIANO,        //53 Choir Aahs
    PIANO,        //54 Voice Oohs
    PIANO,        //55 Synth Voice
    PIANO,        //56 Orchestra Hit
    BRASS,        //57 Trumpet
    BRASS,        //58 Trombone
    BRASS,        //59 Tuba
    BRASS,        //60 Muted Trumpet
    BRASS,        //61 French Horn
    BRASS,        //62 Brass Section
    BRASS,        //63 Synth Brass 1
    BRASS,        //64 Synth Brass 2
    BRASS,        //65 Soprano Sax
    BRASS,        //66 Alto Sax
    BRASS,        //67 Tenor Sax
    BRASS,        //68 Baritone Sax
    BRASS,        //69 Oboe
    BRASS,        //70 English Horn
    BRASS,        //71 Bassoon
    BRASS,        //72 Clarinet
    REED,         //73 Piccolo
    REED,         //74 Flute
    REED,         //75 Recorder
    REED,         //76 Pan Flute
    REED,         //77 Blown bottle
    REED,         //78 Shakuhachi
    REED,         //79 Whistle
    REED,         //80 Ocarina
    [](double frequency, double time){return VSSynth::Waveforms::square(frequency, time);},        //81 Lead 1 (square)
    [](double frequency, double time){return VSSynth::Waveforms::sawtooth(frequency, time);},        //82 Lead 2 (sawtooth)
    PIANO,        //83 Lead 3 (calliope)
    PIANO,        //84 Lead 4 (chiff)
    PIANO,        //85 Lead 5 (charang)
    PIANO,        //86 Lead 6 (voice)
    PIANO,        //87 Lead 7 (fifths)
    PIANO,        //88 Lead 8 (bass + lead)
    PIANO,        //89 Pad 1 (new age)
    PIANO,        //90 Pad 2 (warm)
    PIANO,        //91 Pad 3 (polysynth)
    PIANO,        //92 Pad 4 (choir)
    PIANO,        //93 Pad 5 (bowed)
    PIANO,        //94 Pad 6 (metallic)
    PIANO,        //95 Pad 7 (halo)
    PIANO,        //96 Pad 8 (sweep)
    PIANO,        //97 FX 1 (rain)
    PIANO,        //98 FX 2 (soundtrack)
    PIANO,        //99 FX 3 (crystal)
    PIANO,        //100 FX 4 (atmosphere)
    PIANO,        //101 FX 5 (brightness)
    PIANO,        //102 FX 6 (goblins)
    PIANO,        //103 FX 7 (echoes)
    PIANO,        //104 FX 8 (sci-fi)
    PIANO,        //105 Sitar
    PIANO,        //106 Banjo
    PIANO,        //107 Shamisen
    PIANO,        //108 Koto
    PIANO,        //109 Kalimba
    PIANO,        //110 Bag pipe
    PIANO,        //111 Fiddle
    PIANO,        //112 Shanai
    PIANO,        //113 Tinkle Bell
    PIANO,        //114 Agogô
    PIANO,        //115 Steel Drums
    PIANO,        //116 Woodblock
    PIANO,        //117 Taiko Drum
    PIANO,        //118 Melodic Tom
    PIANO,        //119 Synth Drum
    CYMBAL,       //120 Reverse Cymbal
    PIANO,        //121 Guitar Fret Noise
    PIANO,        //122 Breath Noise
    PIANO,        //123 Seashore
    PIANO,        //124 Bird Tweet
    PIANO,        //125 Telephone Ring
    PIANO,        //126 Helicopter
    PIANO,        //127 Applause
    PIANO         //128 Gunshot
};