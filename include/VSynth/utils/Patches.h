#pragma once

#include "Envelope.h"
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
            return 0.5 * (Waveforms::sine(freq, time) +
                          0.5 * Waveforms::sine(freq * 2, time) +
                          0.25 * Waveforms::sine(freq * 3, time));
        };
        const ADSREnvelope PIANO_ENVELOPE(0.90f, 0.30f, 0.1f, 0.1f, 0.30f);

        const Patch BRASS = [](double freq, double time) {
            return 0.5 * (Waveforms::pulse(freq, time, 25) + 0.25 * Waveforms::sawtooth(freq, time) + 0.0001 * Waveforms::noise());
        };
        const ADSREnvelope BRASS_ENVELOPE(0.90f, 0.30f, 0.1f, 0.1f, 0.05f);

        const Patch REED = [](double freq, double time) {
            return 0.5 * (Waveforms::triangle(freq * 2, time) + 0.5 * Waveforms::sine(freq, time) + 0.25 * Waveforms::sawtooth(freq, time) + 0.04 * Waveforms::noise());
        };
        const ADSREnvelope REED_ENVELOPE(0.90f, 0.30f, 0.1f, 0.1f, 0.05f);

        const Patch GLOCKENSPIEL = [](double freq, double time) {
            return 0.5 * (Waveforms::sine(freq * 2, time) + 0.0001 * Waveforms::noise());
        };
        const ADSREnvelope GLOCKENSPIEL_ENVELOPE(0.90f, 0.30f, 0.1f, 0.1f, 1.00f, true);

        const Patch BASS = [](double freq, double time) {
            return 0.5 * (Waveforms::pulse(freq / 2, time, 10) +
                          0.5 * (Waveforms::square(freq, time)) + 0.0001 * Waveforms::noise());
        };
        const ADSREnvelope BASS_ENVELOPE(1.00f, 0.15f, 0.001f, 0.1f, 0.80f, false);

        const Patch GUITAR = [](double freq, double time) {
            return 0.5 * (Waveforms::pulse(freq, time, 10) +
                          0.5 * (Waveforms::square(freq * 2, time)) + 0.0001 * Waveforms::noise());
        };
        const ADSREnvelope GUITAR_ENVELOPE(1.00f, 0.15f, 0.001f, 0.1f, 0.80f, false);

        const Patch ORGAN = [](double freq, double time) {
            return 0.5 * (Waveforms::sine(freq, time) +
                          0.5 * Waveforms::sine(freq * 2, time) +
                          0.25 * Waveforms::sine(freq * 4, time) +
                          0.125 * Waveforms::sine(freq * 8, time) +
                          0.0625 * Waveforms::sine(freq * 16, time) +
                          0.03125 * Waveforms::sine(freq * 32, time) +
                          0.015625 * Waveforms::sine(freq * 64, time));
        };
        const ADSREnvelope ORGAN_ENVELOPE(0.90f, 0.30f, 0.1f, 0.1f, 0.40f);

        const Patch CYMBAL = [](double freq, double time) {
            return 0.25 * Waveforms::noise();
        };
        const ADSREnvelope CYMBAL_ENVELOPE(0.90f, 0.30f, 0.001f, 0.5f, 1.00f);

    }; // namespace Patches
};     // namespace VSynth