#include <SDL2/SDL.h>
#include <functional>

#include "Envelope.h"
#include "Waveforms.h"

#define FREQUENCY 350
#define AMPLITUDE 9000
#define SAMPLING_RATE 48000

const double sampleDeltaTime = 1.0f / (double) SAMPLING_RATE;

struct Instrument {
    std::function<double (int, double)> wave;
    VSynth::Envelope *envelope;
    double *time;
};

void fillBuffer(void* userData, Uint8* buffer, int length) {
    Sint16 *sampleBuffer = (Sint16 *) buffer;
    Instrument *instruments = (Instrument *) userData;
    double *time = instruments->time;

    int numToWrite = length / (sizeof(Sint16) * 2);
    for(int sample = 0; sample < numToWrite; sample++){
        Sint16 sampleValue = 0;
        *time += sampleDeltaTime;
        instruments->envelope->updateTime(sampleDeltaTime);
        sampleValue = instruments->wave(FREQUENCY, *time)
        * instruments->envelope->getAmplitude()
        * AMPLITUDE;
        *sampleBuffer++ = sampleValue; // Left channel value
        *sampleBuffer++ = sampleValue; // Right channel value
    }
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window *window;
    window = SDL_CreateWindow("SDL_Test_Windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    double time = 0;

    VSynth::ADSREnvelope pianoADSR;
    pianoADSR.attackTime = 0.10f;
    pianoADSR.decayTime = 0.20f;
    pianoADSR.releaseTime = 0.40f;
    pianoADSR.attack = 1.0f;
    pianoADSR.sustain = 0.8f;
    VSynth::Envelope e4Envelope(pianoADSR);
    VSynth::Envelope f4Envelope(pianoADSR);

    std::function<double (int, double)>
        wave(VSynth::Waveforms::sine);

    Instrument instrument;
    instrument.envelope = &e4Envelope;
    instrument.wave = wave;
    instrument.time = &time;

    SDL_AudioSpec obtained = {};
    SDL_AudioSpec requested = {};
    requested.channels = 2;
    requested.samples = 4096;
    requested.format = AUDIO_S16;
    requested.freq = SAMPLING_RATE;
    requested.userdata = &instrument;
    requested.callback = &fillBuffer;

    SDL_AudioDeviceID deviceID = SDL_OpenAudioDevice(nullptr, 0, &requested, &obtained, 0);

    SDL_PauseAudioDevice(deviceID, 0);

    bool running = true;
    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0){
            if(e.type == SDL_QUIT){
                running = false;
            }else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_e){
                    instrument.envelope->hold();
                }else if(e.key.keysym.sym == SDLK_f){
                    instrument.envelope->hold();
                }
            }else if(e.type == SDL_KEYUP){
                if(e.key.keysym.sym == SDLK_e){
                    instrument.envelope->release();
                }else if(e.key.keysym.sym == SDLK_f){
                    instrument.envelope->release();
                }
            }
        }
    }
    
    SDL_PauseAudioDevice(deviceID, 1);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}