#include <VSynth/generators/Sequencer.h>

#include <algorithm>

namespace VSynth
{
    namespace Generators
    {

        Sequencer::Sequencer(Instrument *instrument)
            : mInstrument(instrument),
              mStartTime(0),
              mCurTime(0),
              mLoop(false)
        {
        }

        Sequencer::~Sequencer()
        {
        }

        double Sequencer::sample(double time)
        {
            mCurTime = time;

            // Play all notes ready to be enqueued
            while (
                mEventIt != mEvents.end() &&
                (mEventIt->second < (mCurTime - mStartTime)))
            {
                NoteEvent ev = mEventIt->first;
                if (ev.hold)
                {
                    mInstrument->holdNote(ev.note);
                }
                else
                {
                    mInstrument->releaseNote(ev.note);
                }
                mEventIt++;
            }

            // Loop if needed
            if (mEventIt == mEvents.end() && mLoop)
            {
                mEventIt = mEvents.begin();
                mStartTime = time;
                mCurTime = time;
            }

            return mInstrument->sample(time);
        }

        void Sequencer::queueNote(double note, double startTime, double duration)
        {
            mEvents.push_back({{note, true}, startTime});
            mEvents.push_back({{note, false}, startTime + duration});
            mEventIt = mEvents.begin();
        }

        void Sequencer::sortNotes()
        {
            std::sort(
                mEvents.begin(),
                mEvents.end(),
                [](const auto &rhs, const auto &lhs) {
                    return rhs.second < lhs.second;
                });

            mEventIt = mEvents.begin();
        }

        void Sequencer::setLooping(bool loop)
        {
            mLoop = loop;
        }

    }; // namespace Generators
} // namespace VSynth