#include <VSynth/Generators/Instrument.h>

#include <algorithm>

namespace VSynth
{

    Instrument::Instrument(
        std::function<double(double, double)> wave,
        const ADSREnvelope &adsr)
        : mWave(wave), mADSR(adsr)
    {
    }

    Instrument::~Instrument()
    {
    }
} // namespace VSynth