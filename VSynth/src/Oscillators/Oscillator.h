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
         * @brief Get the next sample for the oscillator 
         * @param deltaTime - the time since last sample in nanoseconds 
         * @return float value between -1.0f and 1.0f 
         */
        float nextSample(double deltaTime);

    protected:

        /**
         * @brief Generates the next sample for the oscillator
         * @return float value between -1.0f and 1.0f
         */
        virtual float generateNextSample() = 0;

        /**
         * @brief Updates the current timestep of the oscillator
         * @param deltaTime 
         */
        void updateTime(double deltaTime);

        /**
         * @brief Converts frequency to radians
         * @return double 
         */
        double freqToRad();

        unsigned int mFrequency; // the frequency of the oscillator 
        double mTime; // The current time in seconds
};

}};