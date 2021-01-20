#include <VSSynth/utils/Waveforms.h>

#include <cmath>
#include <cstdlib>
#define _USE_MATH_DEFINES // PI definition

namespace VSSynth
{
    namespace Waveforms
    {

        const double pulse(double frequency, double time, double percent, double phase)
        {
            percent /= 100;
            double period = 1.0 / frequency;
            double offset = fmod(time + phase, period);
            return offset > (percent * period) ? 1.0 : -1.0;
        }

        const double square(double frequency, double time, double phase)
        {
            frequency += (phase / (time * 2.0 * 3.1415926535)); // Allows for LFO
            double period = 1.0 / frequency;
            double offset = fmod(time, period);
            return offset > (0.5 * period) ? 1.0 : -1.0;
        }

        const double freqToRad(double frequency)
        {
            return frequency * 2.0 * 3.1415926535;
        }

        const double sine(double frequency, double time, double phase)
        {
            return sin(freqToRad(frequency) * time + phase);
        }

        const double sawtooth(double frequency, double time, double phase)
        {
            frequency += (phase / (time * 2.0 * 3.1415926535)); // Allows for LFO
            return 2 * frequency * fmod(time, (1.0f / (float)frequency)) - 1;
        }

        const double triangle(double frequency, double time, double phase)
        {
            return asin(sin(freqToRad(frequency) * time + phase));
        }

        const double noise()
        {
            return (rand() % 3) - 1;
        }

    }; // namespace Waveforms
};     // namespace VSSynth