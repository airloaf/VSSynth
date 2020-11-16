#include "Envelope.h"

namespace VSynth
{

    Envelope::Envelope(ADSREnvelope adsr):
    mPressed(false), mActive(false), mADSR(adsr)
    {
    }

    Envelope::~Envelope()
    {
    }

    double linearInterpolate(double start, double end, double length, double offset){
        return ((offset / length) * (end - start)) + start;
    }

    double Envelope::getAmplitude()
    {
        double amplitude = 0;
        if(mActive){
            if(mPressed){
                if(mTime < mADSR.attackTime){
                    amplitude = linearInterpolate(0, mADSR.attack, mADSR.attackTime, mTime);
                }else if(mTime < (mADSR.decayTime + mADSR.attackTime)){
                    amplitude = linearInterpolate(mADSR.attack, mADSR.sustain, mADSR.decayTime, mTime - mADSR.attackTime);
                }else{
                    amplitude = mADSR.sustain;
                }
            }else{
                amplitude = linearInterpolate(mADSR.sustain, 0, mADSR.releaseTime, mTime - mReleaseStart);
            }
        }

        return amplitude;
    }

    void Envelope::updateTime(double deltaTime)
    {
        if(mActive){
            mTime += deltaTime;
            if(mReleaseStart != 0){
                if(mTime > (mReleaseStart + mADSR.releaseTime)){
                    mActive = false;
                }
            }
        }
    }

    void Envelope::press()
    {
        if(!mPressed){
            mActive = true;
            mPressed = true;
            mTime = 0;
            mReleaseStart = 0;
        }
    }

    void Envelope::release()
    {
        mPressed = false;
        mReleaseStart = mTime;
    }

}; // namespace VSynth