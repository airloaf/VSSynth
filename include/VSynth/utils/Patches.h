#pragma once

#include "Waveforms.h"

namespace VSynth
{

    /**
     * @brief A collection of different synth patches
     */
    namespace Patches
    {
        /**
         * @brief A Patch takes a frequency and time. It outputs a signed value between -1.0 and 1.0
         * 
         */
        typedef std::function<double(double, double)> Patch;

        const Patch PIANO = [](double freq, double time) {
            // return 0.5 * (Waveforms::sine(freq, time) +
            //               0.5 * Waveforms::sine(freq * 2, time) +
            //               0.25 * Waveforms::sine(freq * 3, time) +
            //               0.125 * Waveforms::sine(freq * 4, time) +
            //               0.0625 * Waveforms::sine(freq * 5, time) +
            //               0.03125 * Waveforms::sine(freq * 6, time) +
            //               0.015625 * Waveforms::sine(freq * 7, time));
            return 0.5 * (Waveforms::sine(freq, time) +
                          0.5 * Waveforms::sine(freq * 2, time) +
                          0.25 * Waveforms::sine(freq * 3, time));
        };

        const Patch XYLOPHONE = [](double freq, double time) {
            return 0.5 * (Waveforms::triangle(freq, time) +
                          0.5 * Waveforms::triangle(freq, time) +
                          0.25 * Waveforms::triangle(freq, time) +
                          0.125 * Waveforms::triangle(freq, time) +
                          0.0625 * Waveforms::triangle(freq, time) +
                          0.03125 * Waveforms::triangle(freq, time) +
                          0.015625 * Waveforms::triangle(freq, time));
        };

        const Patch ORGAN = [](double freq, double time) {
            return 0.5 * (Waveforms::sine(freq, time) +
                          0.5 * Waveforms::sine(freq * 2, time) +
                          0.25 * Waveforms::sine(freq * 4, time) +
                          0.125 * Waveforms::sine(freq * 8, time) +
                          0.0625 * Waveforms::sine(freq * 16, time) +
                          0.03125 * Waveforms::sine(freq * 32, time) +
                          0.015625 * Waveforms::sine(freq * 64, time));
        };
    }; // namespace Patches
};     // namespace VSynth