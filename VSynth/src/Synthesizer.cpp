#include "Envelope.h"
#include "Waveforms.h"
#include "Synthesizer.h"

#define FREQUENCY 350
#define AMPLITUDE 3000
#define SAMPLING_RATE 48000

namespace VSynth
{
    const double sampleDeltaTime = 1.0f / (double)SAMPLING_RATE;

    void fillBuffer(void *userData, Uint8 *buffer, int length)
    {
        Sint16 *sampleBuffer = (Sint16 *)buffer;
        SynthData *synthData = (SynthData *) userData;

        int numToWrite = length / (sizeof(Sint16) * 2);
        for (int sample = 0; sample < numToWrite; sample++)
        {
            Sint16 sampleValue = 0;

            for (auto it = synthData->instruments.begin(); it != synthData->instruments.end(); it++)
            {
                Sint16 instrumentSample = 0;
                
                *(synthData->time) += sampleDeltaTime;
                // it->envelope->updateTime(sampleDeltaTime);
                
                instrumentSample = it->wave(*(synthData->time))
                // * it->envelope->getAmplitude()
                * it->amplitude;
                
                sampleValue += instrumentSample;
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

    // std::vector<Instrument> createInstruments()
    // {
    //     std::vector<Instrument> instruments;
    //     ADSREnvelope pianoADSR(0.10f, 0.20f, 0.40f, 1.0f, 0.3f);
    //     Envelope e4Envelope(pianoADSR);
    //     Envelope f4Envelope(pianoADSR);

    //     std::function<double(double)> wave =
    //         std::bind(Waveforms::sine, 5, std::placeholders::_1);

    //     Instrument e4;
    //     e4.envelope = new Envelope(pianoADSR);
    //     e4.wave = std::bind(Waveforms::modulatedWave, 330, std::placeholders::_1, 0.01, wave, Waveforms::square);

    //     Instrument f4;
    //     f4.envelope = new Envelope(pianoADSR);
    //     f4.wave = std::bind(Waveforms::modulatedWave, 350, std::placeholders::_1, 0.01, wave, Waveforms::square);

    //     instruments.push_back(e4);
    //     instruments.push_back(f4);
    //     return instruments;
    // }

    void Synthesizer::open()
    {
        mTime = 0;
        mSynthData.time = &mTime;
        Instrument e4;
        e4.envelope = nullptr;
        // e4.wave = std::bind(Waveforms::modulatedWave, 330, std::placeholders::_1, 0.01, wave, Waveforms::square);
        e4.wave = std::bind(Waveforms::sine, 330, std::placeholders::_1);
        std::function<double (double)> wave = std::bind(Waveforms::sine, 5, std::placeholders::_1);
        e4.wave = std::bind(Waveforms::modulatedWave, 330, std::placeholders::_1, 0.01, wave, Waveforms::square);
        e4.amplitude = 4000;
        mSynthData.instruments.push_back(e4);

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