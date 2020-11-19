#pragma once

namespace VSynth
{
    namespace Waveforms
    {

        double square(unsigned int frequency, double time);
        double sine(unsigned int frequency, double time);
        double sawtooth(unsigned int frequency, double time);
        double triangle(unsigned int frequency, double time);
    }; // namespace Waveforms
}; // namespace VSynth
