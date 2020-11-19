#include "Waveforms.h"

#define _USE_MATH_DEFINES // PI definition
#include <cmath>

namespace VSynth
{
    namespace Waveforms
    {

        double square(unsigned int frequency, double time){
            double period = 1.0 / frequency;
            double offset = fmod(time, period);
            return offset > (0.5 * period)? 1.0: -1.0;
        }

        
        double freqToRad(unsigned int frequency){
            return frequency * 2.0f * M_PI;
        }

        double sine(unsigned int frequency, double time){
            return sin(freqToRad(frequency) * time);
        }

        double sawtooth(unsigned int frequency, double time)
        {
            return 2 * frequency* fmod(time, (1.0f / (float) frequency)) - 1;
        }

        double triangle(unsigned int frequency, double time){
            return asin(sin(freqToRad(frequency) * time));
        }

    }; // namespace Waveforms
}; // namespace VSynth