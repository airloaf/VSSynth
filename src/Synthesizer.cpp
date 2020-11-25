#include <VSynth/Envelope.h>
#include <VSynth/Synthesizer.h>
#include <VSynth/Waveforms.h>

#define FREQUENCY 350
#define AMPLITUDE 3000
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
            for (auto it = synthData->instruments.begin(); it != synthData->instruments.end(); ++it)
            {
                Sint16 instrumentSample = 0;

                it->envelope->updateTime(sampleDeltaTime);

                double envAmp = it->envelope->getAmplitude();
                if(envAmp != 0){
                    instrumentSample = it->wave(*(synthData->time)) * it->amplitude * envAmp;
                    sampleValue += instrumentSample;
                }
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
    {
    }

    void Synthesizer::addInstrument(const Instrument instrument)
    {
        mSynthData.instruments.push_back(instrument);
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