#include <VSynth/Synthesizer.h>

namespace VSynth
{
    void fillBuffer(void *userData, Uint8 *buffer, int length)
    {
        Sint16 *sampleBuffer = (Sint16 *)buffer;
        SynthData *synthData = (SynthData *)userData;
        double sampleDeltaTime = synthData->sampleDeltaTime;

        // Write samples to audio buffer
        int numToWrite = length / (sizeof(Sint16) * 2);
        for (int sample = 0; sample < numToWrite; sample++)
        {
            Sint16 sampleValue = 0;

            *(synthData->time) += sampleDeltaTime;
            for (auto it = synthData->soundGenerators.begin(); it != synthData->soundGenerators.end(); ++it)
            {
                sampleValue += (*it)->sample(*(synthData->time)) * (*it)->getAmplitude();
            }

            *sampleBuffer++ = sampleValue; // Left channel value
            *sampleBuffer++ = sampleValue; // Right channel value
            synthData->writer->writeSample(sampleValue);
        }
    }

    Synthesizer::Synthesizer(unsigned int samplingRate, unsigned int numFrames)
        : mSamplingRate(samplingRate), mNumFrames(numFrames)
    {
        mSynthData.sampleDeltaTime = 1.0 / (double)mSamplingRate;
        mSynthData.time = &mTime;
        mSynthData.writer = &mWAVWriter;
    }

    Synthesizer::~Synthesizer()
    {
    }

    void Synthesizer::addSoundGenerator(SoundGenerator *soundGenerator)
    {
        mSynthData.soundGenerators.push_back(soundGenerator);
    }

    void Synthesizer::open()
    {
        mWAVWriter.open("SOUND_OUT.wav");
        mTime = 0;

        SDL_AudioSpec obtained = {};
        SDL_AudioSpec requested = {};
        requested.freq = mSamplingRate;
        requested.samples = mSamplingRate / mNumFrames;
        requested.format = AUDIO_S16;
        requested.channels = 2;
        requested.userdata = &mSynthData;
        requested.callback = &fillBuffer;

        mDeviceID = SDL_OpenAudioDevice(nullptr, 0, &requested, &obtained, 0);
    }

    void Synthesizer::close()
    {
        SDL_CloseAudioDevice(mDeviceID);
        mWAVWriter.close();
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