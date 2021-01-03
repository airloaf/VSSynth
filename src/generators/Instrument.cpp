#include <VSynth/generators/Instrument.h>

#include <algorithm>

namespace VSynth
{

    Instrument::Instrument(
        std::function<double(double, double)> wave)
        : mWave(wave)
    {
    }

    Instrument::~Instrument()
    {
    }
} // namespace VSynth
