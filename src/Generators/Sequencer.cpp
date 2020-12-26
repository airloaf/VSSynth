#include <VSynth/generators/Sequencer.h>

#include <algorithm>

namespace VSynth
{

    Sequencer::Sequencer(Instrument *instrument)
        : mInstrument(instrument),
          mPrev(0),
          mTime(0)
    {
    }

    Sequencer::~Sequencer()
    {
    }

    double Sequencer::sample(double time)
    {

        double delta = time - mPrev;
        mPrev = time;

        mTime += delta;
        if (mEventIt != mEvents.end())
        {
            if (mEventIt->second < mTime)
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

}; // namespace VSynth