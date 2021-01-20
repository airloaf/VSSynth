#include <VSSynth/SoundGenerator.h>

#include <algorithm>

// MAX amplitude for a waveform
// Amplitude must fit in a 16 bit signed integer
static const double MAX_AMPLITUDE = 6000;

namespace VSSynth
{

    SoundGenerator::SoundGenerator()
        : mAmplitude(MAX_AMPLITUDE)
    {
    }
    SoundGenerator::~SoundGenerator()
    {
    }

    double linearToLog(double linear)
    {
        return ((exp(linear) - 1) / 1.718);
    }

    double logToLinear(double logarithmic)
    {
        return log((logarithmic * 1.718) + 1);
    }

    void SoundGenerator::setVolume(double percent)
    {
        // Adjust percent to be in the range of [0,100]
        percent = std::max(percent, 0.0);
        percent = std::min(percent, 100.0);

        // Logarithmic (exponential) scale
        mAmplitude = linearToLog(percent / 100) * MAX_AMPLITUDE;
    }

    double SoundGenerator::getVolume()
    {
        return logToLinear(mAmplitude / MAX_AMPLITUDE) * 100;
    }

    double SoundGenerator::getAmplitude()
    {
        return mAmplitude;
    }

}; // namespace VSSynth