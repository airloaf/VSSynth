#include <VSSynth/generators/Instrument.h>

#include <algorithm>

namespace VSSynth
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
} // namespace VSSynth