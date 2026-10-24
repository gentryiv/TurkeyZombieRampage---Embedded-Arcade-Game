#ifndef ZOMBIE_POISON_PILL_H
#define ZOMBIE_POISON_PILL_H

#include "screenObject.h"

extern int npcSpeedFactor;

class ZombiePoisonPill : public Poison
{
public:
    ZombiePoisonPill();

    virtual void draw();
    virtual void erase();
    virtual void move();
};

#endif
