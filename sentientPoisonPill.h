#ifndef SENTIENT_POISON_PILL_H
#define SENTIENT_POISON_PILL_H

#include "screenObject.h"

// global turkey from gobbleBuzz.cpp
class GobbleBuzz;
extern GobbleBuzz turkey;

extern int npcSpeedFactor;

class SentientPoisonPill : public Poison
{
public:
    SentientPoisonPill();

    virtual void draw();
    virtual void erase();
    virtual void move();   // override: pursue the player
};

#endif
