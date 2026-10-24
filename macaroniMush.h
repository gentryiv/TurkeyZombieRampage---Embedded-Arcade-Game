#ifndef MACARONI_MUSH_H
#define MACARONI_MUSH_H

#include "screenObject.h"

extern int npcSpeedFactor;

class MacaroniMush : public Food
{
public:
    MacaroniMush();

    virtual void draw();
    virtual void erase();
    virtual void move();
};

#endif
