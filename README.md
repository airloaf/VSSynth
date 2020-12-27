# VSynth

Audio synthesizer library for SDL2. Written in C++.

## Features

- Primitive waveforms (Sine, Square, Sawtooth, Triangle)
- ADSR envelopes
- Polyphony
- Sequencer
- Prebuilt synth patches (Piano, Organ, Xylophone)
- Volume control
- [Doxygen Documentation](https://airloaf.github.io/VSynth/html/index.html)

## Dependencies

- CMake (Version 3.9 is specified, but lower versions will probably work fine)
- SDL2

## How to build

Use the accompanying CMakeLists.txt to generate your project. CMake will generate a library called "VSynth", which you should link to your executables. CMake will also generate some examples as listed below.

## Examples

|Example|Description|
| --- | --- |
| [Piano](https://github.com/airloaf/VSynth/tree/master/examples/piano) | A piano which can play notes on keyboard input. |
| [Sequenced Beats](https://github.com/airloaf/VSynth/tree/master/examples/sequenced_beat) | Extension of the Piano example. The song, "Mary had a little lamb", will play on repeat in the background while you control the  piano. |

## Resources

- [Note/Frequency conversion table](https://pages.mtu.edu/~suits/notefreqs.html)
- [Online tone generator](https://www.szynalski.com/tone-generator/)
- [SDL 2 audio buffer explanation](https://ericscrivner.me/2017/10/getting-circular-sdl-audio/)
- [javidx9/OneLoneCoder synthesizer series](https://youtu.be/tgamhuQnOkM)
