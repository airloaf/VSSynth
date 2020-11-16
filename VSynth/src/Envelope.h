#pragma once

namespace VSynth
{

/**
 * @brief ADSR envelope
 * This envelope should be used to modulate the amplitude of a waveform.
 */
struct ADSREnvelope{
    double attack, sustain;
    double attackTime, decayTime, releaseTime;
};

class Envelope
{
    public:
        Envelope(ADSREnvelope adsr);
        virtual ~Envelope();

        double getAmplitude();
        void updateTime(double deltaTime);

        void press();
        void release();

    private:

        ADSREnvelope mADSR;
        double mTime;
        double mReleaseStart;

        bool mPressed;
        bool mActive;
};
}; // namespace VSynth