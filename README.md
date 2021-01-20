<center>
<img src="branding/LogoLarge.png"/>
</center>

<h2>
    Audio synthesizer library for SDL2. Written in C++.
</h2>

<h2>
    <a href="https://airloaf.github.io/VSynth">VSSynth Website</a>
</h2>

## Features

- Primitive waveforms (Sine, Square, Sawtooth, Triangle, Noise)
- ADSR (Attack Decay Sustain Release) envelopes
- Polyphony
- WAV file output
- LFO (Low Frequency Oscillation)
- Sequencer
- Sample synth patches (Guitar, Piano, Glockenspiel, etc.)
- Volume control

## Use Cases

There are many things you could possibly make with VSSynth!

- Chiptune playback/composition
- Digital Keyboard
- Retro console emulators (NES, Genesis, Atari, Chip-8 interpreter) 
- Video games (Mario Paint, Minecraft Note Block)

## Dependencies

- [CMake](https://cmake.org/) (Version 3.9 is specified, but lower versions will probably work fine)
- [SDL2](https://www.libsdl.org/)

## How to build

Use the accompanying CMakeLists.txt to generate your project. You will need to change some of the variables to reflect your development environment.

The CMake files will generate a library called "VSSynth", which you should link to your executables. CMake can also generate some examples as listed below.

## Examples

|Example|Description|
| --- | --- |
| [Simple Tone](https://github.com/airloaf/VSynth/tree/master/examples/SimpleTone) | The "Hello World!" of VSSynth. Produces a Sine Wave with the note C4. |
| [Low Frequency Oscillator](https://github.com/airloaf/VSynth/tree/master/examples/LowFrequencyOscillator) | Produces a Sawtooth Wave with a low frequency oscillator attached. |
| [Record Tone](https://github.com/airloaf/VSynth/tree/master/examples/RecordTone) | Produces a WAVE file with a Sine Wave with the note C4. |
| [Piano](https://github.com/airloaf/VSynth/tree/master/examples/piano) | A piano which can play notes on keyboard input. |
| [Sequenced Beat](https://github.com/airloaf/VSynth/tree/master/examples/sequenced_beat) | Extension of the Piano example. The song, "Mary had a little lamb", will play on repeat in the background while you control the  piano. |
| [MIDI Player](https://github.com/airloaf/VSynth/tree/master/examples/MIDI) | A MIDI player using synthesized instruments included with VSSynth. Does not fully support all MIDI messages, but the majority of songs play well on this. |

## Resources

- [Note/Frequency conversion table](https://pages.mtu.edu/~suits/notefreqs.html)
- [Online tone generator](https://www.szynalski.com/tone-generator/)
- [SDL 2 audio buffer explanation](https://ericscrivner.me/2017/10/getting-circular-sdl-audio/)
- [javidx9/OneLoneCoder synthesizer series](https://youtu.be/tgamhuQnOkM)
