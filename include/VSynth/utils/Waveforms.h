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
         * @brief Generates a 50% pulse wave
         * 
         * @param frequency
         * @param time 
         * @return double 
         */
        const double square(double frequency, double time);

        /**
         * @brief Generates a sine wave
         * 
         * @param frequency 
         * @param time 
         * @return double 
         */
        const double sine(double frequency, double time);

        /**
         * @brief Generates a sawtooth wave
         * 
         * @param frequency 
         * @param time 
         * @return double 
         */
        const double sawtooth(double frequency, double time);

        /**
         * @brief Generates a triangle wave
         * 
         * @param frequency 
         * @param time 
         * @return double 
         */
        const double triangle(double frequency, double time);

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
