#pragma once

namespace VSynth{ namespace Oscillator{

/**
 * @brief Oscillator representation
 */
class Oscillator{
    public:
        Oscillator(unsigned int frequency);
        ~Oscillator();

        /**
         * @brief Get the next sample for the waveform
         * @param deltaTime - the time since last sample in nanoseconds 
         * @return float value between -1.0f and 1.0f 
         */
        virtual float nextSample(double deltaTime) = 0;

        /**
         * @brief Resets the oscillator
         */
        void reset();

    protected:

        /**
         * @brief Updates the current timestep of the oscillator
         * @param deltaTime 
         */
        void updateTime(double deltaTime);

        /**
         * @brief Percent oscillator has gone through
         * @return float 
         */
        float percentageComplete();

        double mDuration; // the duration for a single oscillation in nanoseconds 
        double mTime; // The current time in nanoseconds 
};

}};