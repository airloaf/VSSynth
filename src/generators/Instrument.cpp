#include <VSynth/generators/Instrument.h>

#include <algorithm>

namespace VSynth
{
    namespace Generators
    {

        Instrument::Instrument(
            std::function<double(double, double)> wave)
            : mWave(wave)
        {
        }

        Instrument::~Instrument()
        {
        }

    } // namespace Generators
} // namespace VSynth