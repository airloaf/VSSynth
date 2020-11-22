#include <SDL2/SDL.h>
#include <vector>

#include "Envelope.h"
#include "Waveforms.h"

#define FREQUENCY 350
#define AMPLITUDE 3000
#define SAMPLING_RATE 48000

using namespace VSynth;

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
    std::vector<Instrument> instruments;
    ADSREnvelope pianoADSR(0.10f, 0.20f, 0.40f, 1.0f, 0.3f);
    Envelope e4Envelope(pianoADSR);
    Envelope f4Envelope(pianoADSR);

    std::function<double (double)> wave =
    std::bind(Waveforms::sine, 5, std::placeholders::_1);

    Instrument e4;
    e4.envelope = new Envelope(pianoADSR);
    e4.wave = std::bind(Waveforms::modulatedWave, 330, std::placeholders::_1, 0.01, wave, Waveforms::square);
    e4.time = new double;
    
    Instrument f4;
    f4.envelope = new Envelope(pianoADSR);
    f4.wave = std::bind(Waveforms::modulatedWave, 350, std::placeholders::_1, 0.01, wave, Waveforms::square);
    f4.time = new double;

    instruments.push_back(e4);
    instruments.push_back(f4);
    return instruments;
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    SDL_Window *window;
    window = SDL_CreateWindow("SDL_Test_Windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    auto instruments = createInstruments();

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