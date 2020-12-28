#pragma once

namespace VSynth
{

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

        virtual double sample(double time) = 0;

        /**
         * @brief Sets the volume at a certain percent
         * 
         * @param percent - volume as a percent in range [0,100]
         */
        void setVolume(double percent);

        /**
         * @brief Gets the current volume as a percent [0, 100]
         * 
         * @return double 
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
         * @return double 
         */
        double getAmplitude();

    protected:
        double mAmplitude;
    };
} // namespace VSynth