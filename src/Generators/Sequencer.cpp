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

    void Sequencer::addNoteEvent(NoteEvent event, double time)
    {
        mEvents.push_back({event, time});
        // Reset the event iterator
        mEventIt = mEvents.begin();
    }

    void Sequencer::sortEvents()
    {
        std::sort(
            mEvents.begin(),
            mEvents.end(),
            [](const auto &rhs, const auto &lhs) {
                return rhs.second < lhs.second;
            });
    }

}; // namespace VSynth