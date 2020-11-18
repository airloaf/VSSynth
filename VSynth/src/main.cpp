#include <SDL2/SDL.h>
#include <list>
#include <vector>

#include "Oscillators/SawTooth.h"
#include "Oscillators/Sine.h"
#include "Oscillators/Square.h"
#include "Oscillators/Triangle.h"
#include "Envelope.h"

#define FREQUENCY 0200
#define AMPLITUDE 05000
#define SAMPLING_RATE 48000

const double sampleDeltaTime = 1.0f / (double) SAMPLING_RATE;

struct Instrument {
    std::list<VSynth::Oscillator::Oscillator *> oscs;
    VSynth::Envelope *env;
};

// Taken from https://ericscrivner.me/2017/10/getting-circular-sdl-audio/
void fillAudioDeviceBuffer(void* userData, Uint8* buffer, int length) {
    Sint16 *sampleBuffer = (Sint16 *) buffer;
    std::vector<Instrument> *instruments = (std::vector<Instrument> *) userData;
    
    // Write the samples to the audio buffer
    int numToWrite = length / (sizeof(Sint16) * 2);
    for(int sample = 0; sample < numToWrite; sample++){
        Sint16 sampleValue = 0;
        // for(auto it = instruments->begin(); it != instruments->end(); it++){
        //     Sint16 instrumentSample = 0;
        //     for(auto it2 = it->oscs.begin(); it2 != it->oscs.end(); it2++){
        //         instrumentSample += (*it2)->nextSample(sampleDeltaTime);
        //     }
        //     it->env->updateTime(sampleDeltaTime);
        //     instrumentSample *= AMPLITUDE * it->env->getAmplitude();
        //     sampleValue += instrumentSample;
        // }
        

        sampleValue = 0;
        for(auto it = instruments->begin(); it != instruments->end(); ++it){
            Sint16 instrumentValue = 1;
            it->env->updateTime(sampleDeltaTime);
            for(auto it2 = it->oscs.begin(); it2 != it->oscs.end(); ++it2){
                instrumentValue *= (*it2)->nextSample(sampleDeltaTime);
            }
            // instrumentValue += it->oscs.front()->nextSample(sampleDeltaTime);
            instrumentValue *= it->env->getAmplitude() * AMPLITUDE;
            sampleValue += instrumentValue;
        }

        // instruments->front().env->updateTime(sampleDeltaTime); 
        // sampleValue = instruments->front().oscs.front()->nextSample(sampleDeltaTime);
        // sampleValue *= instruments->front().env->getAmplitude() * AMPLITUDE;

        *sampleBuffer++ = sampleValue; // Left channel value
        *sampleBuffer++ = sampleValue; // Right channel value
    }
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window *window;
    window = SDL_CreateWindow("SDL_Test_Windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    // Create waveforms
    VSynth::Oscillator::Square e4Wave(330);
    VSynth::Oscillator::Square f4Wave(350);

    VSynth::ADSREnvelope pianoADSR;
    pianoADSR.attackTime = 0.10f;
    pianoADSR.decayTime = 0.20f;
    pianoADSR.releaseTime = 0.40f;
    pianoADSR.attack = 1.0f;
    pianoADSR.sustain = 0.8f;

    VSynth::Envelope e4Envelope(pianoADSR);
    VSynth::Envelope f4Envelope(pianoADSR);


    Instrument e4;
    e4.oscs.push_back(&e4Wave);
    e4.env = &e4Envelope;

    Instrument f4;
    f4.oscs.push_back(&f4Wave);
    f4.env = &f4Envelope;

    std::vector<Instrument> instruments;
    instruments.push_back(e4);
    instruments.push_back(f4);

    SDL_AudioSpec obtained = {};
    SDL_AudioSpec requested = {};
    requested.channels = 2;
    requested.samples = 4096;
    requested.format = AUDIO_S16;
    requested.freq = SAMPLING_RATE;
    requested.userdata = &instruments;
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
                if(e.key.keysym.sym == SDLK_e){
                    instruments[0].env->hold();
                }else if(e.key.keysym.sym == SDLK_f){
                    instruments[1].env->hold();
                }
            }else if(e.type == SDL_KEYUP){
                if(e.key.keysym.sym == SDLK_e){
                    instruments[0].env->release();
                }else if(e.key.keysym.sym == SDLK_f){
                    instruments[1].env->release();
                }
            }
        }
    }
    
    SDL_PauseAudioDevice(deviceID, 1);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}