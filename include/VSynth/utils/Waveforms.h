#pragma once

#include <functional>

namespace VSynth
{
    /**
     * @brief Collection of waveform primitives
     * 
     * This namespace encompasses many of the common waveforms an
     * audio synthesizer would want to use.
     * 
     */
    namespace Waveforms
    {

        /**
         * @brief Generates a pulse wave at a given percent
         * 
         * @param frequency 
         * @param time 
         * @param percent in range [0, 100]
         * @return const double 
         */
        const double pulse(double frequency, double time, double percent, double phase=0);

        /**
         * @brief Generates a 50% pulse wave
         * 
         * @param frequency
         * @param time 
         * @return double 
         */
        const double square(double frequency, double time, double phase=0);

        /**
         * @brief Generates a sine wave
         * 
         * @param frequency 
         * @param time 
         * @return double 
         */
        const double sine(double frequency, double time, double phase=0);

        /**
         * @brief Generates a sawtooth wave
         * 
         * @param frequency 
         * @param time 
         * @return double 
         */
        const double sawtooth(double frequency, double time, double phase=0);

        /**
         * @brief Generates a triangle wave
         * 
         * @param frequency 
         * @param time 
         * @return double 
         */
        const double triangle(double frequency, double time, double phase=0);

        /**
         * @brief Generates random noise
         * 
         * @return const double 
         */
        const double noise();

        /**
         * @brief Generates a waveform with a low frequency oscillator
         * 
         * @param wave - base waveform
         * @param frequency - base frequency
         * @param modulatorAmplitude - modulator amplitude (higher value makes the oscillator more pronounced)
         * @param freqOsc - the frequency oscillator
         * @param time 
         * @return double 
         */
        const double modulatedWave(
            std::function<double(double, double)> wave,
            double frequency,
            double modulatorAmplitude,
            std::function<double(double)> freqOsc,
            double time);

    }; // namespace Waveforms
};     // namespace VSynth
