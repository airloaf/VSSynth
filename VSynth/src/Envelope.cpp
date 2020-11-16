#include "Envelope.h"

namespace VSynth
{

    Envelope::Envelope(const ADSREnvelope adsr):
    mHold(false), mActive(false), mADSR(adsr)
    {
    }

    Envelope::~Envelope()
    {
    }

    double linearInterpolate(double start, double end, double length, double offset){
        return ((offset / length) * (end - start)) + start;
    }

    double Envelope::getAmplitude() const
    {
        double amplitude = 0;
        if(mActive){
            if(mHold){
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
            if(mReleaseStart != 0){ // Check if the release section of the ADSR curve is done
                if(mTime > (mReleaseStart + mADSR.releaseTime)){
                    mActive = false;
                }
            }
        }
    }

    void Envelope::hold()
    {
        if(!mHold){
            mActive = true;
            mHold = true;
            mTime = 0;
            if(mADSR.sustainable){
                mReleaseStart = 0;
            }else{
                mReleaseStart = mADSR.attackTime + mADSR.decayTime;
            }
        }
    }

    void Envelope::release()
    {
        mHold = false;
        mReleaseStart = mTime;
    }

}; // namespace VSynth