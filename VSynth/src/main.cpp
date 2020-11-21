#include <SDL2/SDL.h>
#include <vector>

#include "Envelope.h"
#include "Waveforms.h"

#define FREQUENCY 350
#define AMPLITUDE 3000
#define SAMPLING_RATE 48000

const double sampleDeltaTime = 1.0f / (double) SAMPLING_RATE;

struct Instrument {
    std::function<double (double)> wave;
    VSynth::Envelope *envelope;
    double *time;
};

void fillBuffer(void* userData, Uint8* buffer, int length) {
    Sint16 *sampleBuffer = (Sint16 *) buffer;
    std::vector<Instrument> *instruments = (std::vector<Instrument> *) userData;

    int numToWrite = length / (sizeof(Sint16) * 2);
    for(int sample = 0; sample < numToWrite; sample++){
        Sint16 sampleValue = 0;

        for(auto it = instruments->begin(); it != instruments->end(); it++){
            Sint16 instrumentSample = 0;
            *(it->time) += sampleDeltaTime;
            it->envelope->updateTime(sampleDeltaTime);
            instrumentSample = it->wave(*(it->time))
            * it->envelope->getAmplitude() * AMPLITUDE;
            sampleValue += instrumentSample;
        }

        *sampleBuffer++ = sampleValue; // Left channel value
        *sampleBuffer++ = sampleValue; // Right channel value
    }
}

std::vector<Instrument> createInstruments(){

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
    pianoADSR.sustain = 0.3f;
    VSynth::Envelope e4Envelope(pianoADSR);
    VSynth::Envelope f4Envelope(pianoADSR);

    std::function<double (double)> wave =
    std::bind(VSynth::Waveforms::sine, 5, std::placeholders::_1);

    Instrument instrument;
    instrument.envelope = &e4Envelope;
    instrument.wave = wave;
    instrument.time = &time;

    double e4Time = 0;
    Instrument e4;
    e4.envelope = &e4Envelope;
    e4.wave = std::bind(VSynth::Waveforms::modulatedWave, 330, std::placeholders::_1, 0.01, wave, VSynth::Waveforms::triangle);
    e4.time = &e4Time;
    
    double f4Time = 0;
    Instrument f4;
    f4.envelope = &f4Envelope;
    f4.wave = std::bind(VSynth::Waveforms::modulatedWave, 350, std::placeholders::_1, 0.01, wave, VSynth::Waveforms::triangle);
    f4.time = &f4Time;

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
                    instruments[0].envelope->hold();
                }else if(e.key.keysym.sym == SDLK_f){
                    instruments[1].envelope->hold();
                }
            }else if(e.type == SDL_KEYUP){
                if(e.key.keysym.sym == SDLK_e){
                    instruments[0].envelope->release();
                }else if(e.key.keysym.sym == SDLK_f){
                    instruments[1].envelope->release();
                }
            }
        }
    }
    
    SDL_PauseAudioDevice(deviceID, 1);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}