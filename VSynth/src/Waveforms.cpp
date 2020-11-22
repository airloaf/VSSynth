#include "Waveforms.h"

#include <cmath>
#define _USE_MATH_DEFINES // PI definition

namespace VSynth
{
    namespace Waveforms
    {

        double square(double frequency, double time){
            double period = 1.0 / frequency;
            double offset = fmod(time, period);
            return offset > (0.5 * period)? 1.0: -1.0;
        }

        
        double freqToRad(double frequency){
            return frequency * 2.0 * 3.1415926535;
        }

        double sine(double frequency, double time){
            return sin(freqToRad(frequency) * time);
        }

        double sawtooth(double frequency, double time)
        {
            return 2 * frequency* fmod(time, (1.0f / (float) frequency)) - 1;
        }

        double triangle(double frequency, double time){
            return asin(sin(freqToRad(frequency) * time));
        }
        
        double modulatedWave(
            std::function<double (double, double)> wave,
            double frequency,
            double modulatorAmplitude,
            std::function<double (double)> freqOsc,
            double time
        ){
            // This is ugly, but it works
            return wave(frequency + (modulatorAmplitude * frequency * freqOsc(time) / (time * 2.0 * 3.1415926535)), time);
        }

    }; // namespace Waveforms
}; // namespace VSynth