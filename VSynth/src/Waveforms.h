#pragma once

#include <functional>

namespace VSynth
{
    namespace Waveforms
    {

        double square(double frequency, double time);
        double sine(double frequency, double time);
        double sawtooth(double frequency, double time);
        double triangle(double frequency, double time);

        double modulatedWave(double frequency, double time, double modulatorAmplitude,
            std::function<double (double)> freqOsc,
            std::function<double (double, double)> wave);

    }; // namespace Waveforms
}; // namespace VSynth
