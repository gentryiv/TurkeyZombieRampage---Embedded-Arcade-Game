#ifndef PECAN_PINKIE_H
#define PECAN_PINKIE_H

#include "screenObject.h"

extern int npcSpeedFactor;

class PecanPinkie : public Food
{
public:
    PecanPinkie();

    virtual void draw();
    virtual void erase();
    virtual void move();
};

#endif
