#include <SDL2/SDL.h>

struct AudioSettings{
    int samplesPerSecond;
    int numChannels;
    int bytesPerSample;
    int sampleIndex;
    int toneFrequency;
    int toneVolume;
    int wavePeriod;
};
// Taken from https://ericscrivner.me/2017/10/getting-circular-sdl-audio/
void fillAudioDeviceBuffer(void* userData, Uint8* buffer, int length) {
  AudioSettings *audioSettings = (AudioSettings *)userData;

  Sint16* sampleBuffer = (Sint16 *) buffer;
  int samplesToWrite = length / audioSettings->bytesPerSample;
  for (int sampleIndex = 0; sampleIndex < samplesToWrite; sampleIndex++)
  {
    // Generate a square wave at the given period to produce tone
    Sint16 sampleValue = audioSettings->toneVolume;
    if ((audioSettings->sampleIndex / audioSettings->wavePeriod) % 2)
    {
      sampleValue = -audioSettings->toneVolume;
    }
    *sampleBuffer++ = sampleValue; // Left channel value
    *sampleBuffer++ = sampleValue; // Right channel value
    audioSettings->sampleIndex++; // Count as 1 sample
  }
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    
    SDL_Window *window;
    window = SDL_CreateWindow("SDL_Test_Windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);

    AudioSettings audioSettings = {};
    audioSettings.samplesPerSecond = 48000;
    audioSettings.numChannels = 2;
    audioSettings.bytesPerSample = audioSettings.numChannels * sizeof(Sint16);
    audioSettings.sampleIndex = 0;
    audioSettings.toneVolume = 0500;
    audioSettings.toneFrequency = 263;
    audioSettings.wavePeriod = audioSettings.samplesPerSecond / (audioSettings.toneFrequency * audioSettings.numChannels);

    SDL_AudioSpec requested = {};
    requested.freq = audioSettings.samplesPerSecond;
    requested.channels = audioSettings.numChannels;
    requested.format = AUDIO_S16;
    requested.samples = 4096;
    requested.userdata = &audioSettings;
    requested.callback = &fillAudioDeviceBuffer;

    SDL_AudioSpec obtainedSettings = {};
    SDL_AudioDeviceID deviceID = SDL_OpenAudioDevice(nullptr, 0, &requested, &obtainedSettings, 0);

    SDL_PauseAudioDevice(deviceID, 0);

    bool running = true;
    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}