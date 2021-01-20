#include <VSSynth/generators/Tone.h>

namespace VSSynth
{
    namespace Generators
    {

        Tone::Tone(const std::function<double(double, double)> wave)
            : mWave(wave)
        {
        }

        Tone::~Tone()
        {
        }

        double Tone::sample(double time)
        {
            double sample = 0;

            // Trylock since we don't want the thread that samples to block
            if (mNoteLock.try_lock())
            {
                for (auto it = mNotes.begin(); it != mNotes.end(); it++)
                {
                    sample += mWave(*it, time);
                }
                mNoteLock.unlock();
            }
            return sample;
        }

        void Tone::playNote(double frequency)
        {
            mNoteLock.lock();
            auto it = std::find(mNotes.begin(), mNotes.end(), frequency);
            if (it == mNotes.end())
            {
                mNotes.push_back(frequency);
            }
            mNoteLock.unlock();
        }

        void Tone::stopNote(double frequency)
        {
            mNoteLock.lock();
            auto it = std::find(mNotes.begin(), mNotes.end(), frequency);
            if (it != mNotes.end())
            {
                mNotes.erase(it);
            }
            mNoteLock.unlock();
        }

    }; // namespace Generators
} // namespace VSSynth