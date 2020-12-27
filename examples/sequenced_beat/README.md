# Sequenced Beat

This example shows how to create a simple sequencer to be played in the background. This makes use of the code from the Piano example.

## Usage

A sequencer will play "Mary had a little lamb" in the background on repeat. See README for the Piano example to see the keybindings to play notes while the sequencer runs in the background.

## Code to focus on

See function setSequencerBeat(). It queue's up notes to play the song "Mary had a little lamb". After queueing each of the notes, Sequencer::sortNotes() is called to ensure that the notes are stored sorted by their queue times.
