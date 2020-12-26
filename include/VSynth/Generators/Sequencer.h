#pragma once

#include "Instrument.h"

#include <vector>

namespace VSynth
{

    /**
     * @brief Note events for the sequencer
     * 
     * A note event consists of a note and a boolean representing
     * if the note is to be held or released.
     */
    struct NoteEvent
    {
        double note;
        bool hold;
    };

    /**
     * @brief Note Sequencer for Instruments
     * 
     * A sequencer will queue up notes to be played for the set instrument.
     * 
     */
    class Sequencer : public SoundGenerator
    {
    public:
        Sequencer(Instrument *instrument);
        virtual ~Sequencer();

        double sample(double time);

        void addNoteEvent(NoteEvent event, double time);
        void sortEvents();

    private:
        Instrument *mInstrument;
        double mTime;
        double mPrev;

        std::vector<std::pair<NoteEvent, double>> mEvents;
        std::vector<std::pair<NoteEvent, double>>::iterator mEventIt;
    };

} // namespace VSynth