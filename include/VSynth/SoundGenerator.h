#pragma once

namespace VSynth
{
    /**
     * @brief Collection of sound generators provided with VSynth
     */
    namespace Generators
    {
    }

    /**
     * @brief Sound generator
     * 
     * Interface for creating sound generating devices
     */
    class SoundGenerator
    {
    public:
        SoundGenerator();
        virtual ~SoundGenerator();

        /**
         * @brief Sample the SoundGenerator at the given time
         * 
         * @param time - in seconds
         * @return double - sound sample in range [-1.0,1.0]
         */
        virtual double sample(double time) = 0;

        /**
         * @brief Sets the volume at a certain percent
         * 
         * @param percent - volume as a percent in range [0,100]
         */
        void setVolume(double percent);

        /**
         * @brief Gets the current volume as a percent
         * 
         * @return double - volume as a percent [0, 100]
         */
        double getVolume();

        /**
         * @brief Amplitude for synthesizer
         * 
         * Sound generators, when sampled, return a value in [-1.0, 1.0].
         * This value will be multiplied by the amplitude returned by this
         * function. The amplitude will be a value such that it can fit
         * in a 16-bit signed integer.
         * 
         * This function is mainly for the Synthesizer. You shouldn't
         * really have a reason to call this function.
         * 
         * @return double 
         */
        double getAmplitude();

    protected:
        double mAmplitude;
    };
} // namespace VSynth