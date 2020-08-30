#include <SDL2/SDL.h>

#include "Waveforms/SawTooth.h"
#include "Waveforms/Sine.h"
#include "Waveforms/Square.h"
#include "Waveforms/Triangle.h"

// Taken from https://ericscrivner.me/2017/10/getting-circular-sdl-audio/
void fillAudioDeviceBuffer(void* userData, Uint8* buffer, int length) {
    Sint16 *sampleBuffer = (Sint16 *) buffer;
    VSynth::Waveforms::Waveform *wave = (*(VSynth::Waveforms::Waveform **) userData);
    
    // Write the samples to the audio buffer
    int numToWrite = length / (sizeof(Sint16) * 2);
    for(int sample = 0; sample < numToWrite; sample++){
        Sint16 sampleValue = wave->nextSample();
        *sampleBuffer++ = sampleValue; // Left channel value
        *sampleBuffer++ = sampleValue; // Right channel value
    }
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window *window;
    window = SDL_CreateWindow("SDL_Test_Windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    // Create waveforms
    VSynth::Waveforms::Square square(48000, 262, 5000);
    VSynth::Waveforms::Sine sine(48000, 262, 5000);
    VSynth::Waveforms::SawTooth sawTooth(48000, 262, 5000);
    VSynth::Waveforms::Triangle triangle(48000, 262, 5000);

    VSynth::Waveforms::Waveform *waveform = &square;

    SDL_AudioSpec requested = {};
    requested.freq = 48000;
    requested.channels = 2;
    requested.format = AUDIO_S16;
    requested.samples = 4096;
    requested.userdata = &waveform;
    requested.callback = &fillAudioDeviceBuffer;

    SDL_AudioSpec obtainedSettings = {};
    SDL_AudioDeviceID deviceID = SDL_OpenAudioDevice(nullptr, 0, &requested, &obtainedSettings, 0);

    SDL_PauseAudioDevice(deviceID, 0);

    bool running = true;
    bool paused = false;
    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0){
            if(e.type == SDL_QUIT){
                running = false;
            }else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_p){
                    paused = !paused;
                    SDL_PauseAudioDevice(deviceID, paused? 0: 1);
                }else if(e.key.keysym.sym == SDLK_1){
                    waveform = &square;
                }else if(e.key.keysym.sym == SDLK_2){
                    waveform = &sine;
                }else if(e.key.keysym.sym == SDLK_3){
                    waveform = &sawTooth;
                }else if(e.key.keysym.sym == SDLK_4){
                    waveform = &triangle;
                }
            }
        }
    }
    
    SDL_PauseAudioDevice(deviceID, 1);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}