#include <VSynth/Synthesizer.h>

#define SAMPLING_RATE 48000

namespace VSynth
{
    const double sampleDeltaTime = 1.0f / (double)SAMPLING_RATE;

    void fillBuffer(void *userData, Uint8 *buffer, int length)
    {
        Sint16 *sampleBuffer = (Sint16 *)buffer;
        SynthData *synthData = (SynthData *)userData;

        int numToWrite = length / (sizeof(Sint16) * 2);
        for (int sample = 0; sample < numToWrite; sample++)
        {
            Sint16 sampleValue = 0;

            *(synthData->time) += sampleDeltaTime;
            for (auto it = synthData->soundGenerators.begin(); it != synthData->soundGenerators.end(); ++it)
            {
                sampleValue += (*it)->sample(*(synthData->time)) * 6000.0;
            }

            *sampleBuffer++ = sampleValue; // Left channel value
            *sampleBuffer++ = sampleValue; // Right channel value
        }
    }

    Synthesizer::Synthesizer()
    {
        mSynthData.time = &mTime;
    }

    Synthesizer::~Synthesizer()
    {}

    void Synthesizer::addSoundGenerator(SoundGenerator *soundGenerator)
    {
        mSynthData.soundGenerators.push_back(soundGenerator);
    }

    void Synthesizer::open()
    {
        mTime = 0;

        SDL_AudioSpec obtained = {};
        SDL_AudioSpec requested = {};
        requested.channels = 2;
        requested.samples = 4096;
        requested.format = AUDIO_S16;
        requested.freq = SAMPLING_RATE;
        requested.userdata = &mSynthData;
        requested.callback = &fillBuffer;

        mDeviceID = SDL_OpenAudioDevice(nullptr, 0, &requested, &obtained, 0);
    }

    void Synthesizer::close()
    {
        SDL_CloseAudioDevice(mDeviceID);
    }

    void Synthesizer::unpause()
    {
        SDL_PauseAudioDevice(mDeviceID, 0);
    }

    void Synthesizer::pause()
    {
        SDL_PauseAudioDevice(mDeviceID, 1);
    }

}; // namespace VSynth