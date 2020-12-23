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
        SoundGenerator() {}
        ~SoundGenerator() {}

        virtual double sample(double time) = 0;
    };
} // namespace VSynth