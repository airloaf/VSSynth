#include <SDL2/SDL.h>
#include <list>

#include "Oscillators/SawTooth.h"
#include "Oscillators/Sine.h"
#include "Oscillators/Square.h"
#include "Oscillators/Triangle.h"
#include "Envelope.h"

#define FREQUENCY 0200
#define AMPLITUDE 1000
#define SAMPLING_RATE 48000

const double sampleDeltaTime = 1.0f / (double) SAMPLING_RATE;

struct Instrument {
    std::list<VSynth::Oscillator::Oscillator> oscs;
    VSynth::Envelope *env;
};

struct AudioData {
    VSynth::Oscillator::Oscillator **osc;
    VSynth::Envelope *env;
};

// Taken from https://ericscrivner.me/2017/10/getting-circular-sdl-audio/
void fillAudioDeviceBuffer(void* userData, Uint8* buffer, int length) {
    Sint16 *sampleBuffer = (Sint16 *) buffer;
    //VSynth::Oscillator::Oscillator *wave = (*(VSynth::Oscillator::Oscillator **) userData);
    AudioData *audioData = (*(AudioData **) userData); 
    VSynth::Oscillator::Oscillator *wave = *audioData->osc;
    VSynth::Envelope *env = audioData->env;

    // Write the samples to the audio buffer
    int numToWrite = length / (sizeof(Sint16) * 2);
    for(int sample = 0; sample < numToWrite; sample++){
        env->updateTime(sampleDeltaTime);
        Sint16 sampleValue = (Sint16) (wave->nextSample(sampleDeltaTime) * AMPLITUDE * env->getAmplitude());
        *sampleBuffer++ = sampleValue; // Left channel value
        *sampleBuffer++ = sampleValue; // Right channel value
    }
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window *window;
    window = SDL_CreateWindow("SDL_Test_Windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    // Create waveforms
    VSynth::Oscillator::SawTooth sawTooth(FREQUENCY);
    VSynth::Oscillator::Sine sine(FREQUENCY);
    VSynth::Oscillator::Square square(FREQUENCY);
    VSynth::Oscillator::Triangle triangle(FREQUENCY);

    VSynth::Oscillator::Oscillator *waveform = &square;

    VSynth::ADSREnvelope adsr;
    adsr.attackTime = 0.10f;
    adsr.decayTime = 0.20f;
    adsr.releaseTime = 0.40f;
    adsr.attack = 1.0f;
    adsr.sustain = 0.8f;
    adsr.sustainable = true;
    VSynth::Envelope envelope(adsr);

    AudioData *audioData = new AudioData();
    audioData->osc = &waveform;
    audioData->env = &envelope;

    SDL_AudioSpec obtained = {};
    SDL_AudioSpec requested = {};
    requested.channels = 2;
    requested.samples = 4096;
    requested.format = AUDIO_S16;
    requested.freq = SAMPLING_RATE;
    requested.userdata = &audioData;
    requested.callback = &fillAudioDeviceBuffer;

    SDL_AudioDeviceID deviceID = SDL_OpenAudioDevice(nullptr, 0, &requested, &obtained, 0);

    SDL_PauseAudioDevice(deviceID, 0);

    bool running = true;
    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0){
            if(e.type == SDL_QUIT){
                running = false;
            }else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_SPACE){
                    envelope.hold();
                }
            }else if(e.type == SDL_KEYUP){
                if(e.key.keysym.sym == SDLK_SPACE){
                    envelope.release();
                }
            }
        }
    }
    
    SDL_PauseAudioDevice(deviceID, 1);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}