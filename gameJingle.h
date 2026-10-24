#ifndef STARTUPJINGLE_H
#define STARTUPJINGLE_H

#include "speaker.h"

extern Speaker mySpeaker;

class GameJingle
{
public:
    void playIntro()
    {
        mySpeaker.PlayNote(523.25f, 0.20f, 0.4f);   // C5
        mySpeaker.PlayNote(659.25f, 0.20f, 0.4f);   // E5
        mySpeaker.PlayNote(783.99f, 0.20f, 0.4f);   // G5
        mySpeaker.PlayNote(1046.5f, 0.30f, 0.4f);   // C6
    }

    //not in video so unused but created anyways
    void playWin()
    {
        mySpeaker.PlayNote(659.25f, 0.20f, 0.4f);   // E5
        mySpeaker.PlayNote(783.99f, 0.20f, 0.4f);   // G5
        mySpeaker.PlayNote(880.00f, 0.20f, 0.4f);   // A5
        mySpeaker.PlayNote(987.77f, 0.30f, 0.4f);   // B5
        mySpeaker.PlayNote(1174.66f, 0.30f, 0.4f);  // D6
        mySpeaker.PlayNote(1318.51f, 0.40f, 0.4f);  // E6 (final)
    }

    void playLose()
    {
        mySpeaker.PlayNote(392.00f, 0.25f, 0.4f);   // G4
        mySpeaker.PlayNote(349.23f, 0.25f, 0.4f);   // F4
        mySpeaker.PlayNote(329.63f, 0.25f, 0.4f);   // E4
        mySpeaker.PlayNote(261.63f, 0.40f, 0.4f);   // C4
        mySpeaker.PlayNote(196.00f, 0.40f, 0.4f);   // G3 (final drop)
    }

};

#endif
