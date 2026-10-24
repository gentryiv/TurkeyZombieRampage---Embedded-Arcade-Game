#ifndef CELERY_BRAINS_H
#define CELERY_BRAINS_H

#include "screenObject.h"

extern int npcSpeedFactor;

class CeleryBrains : public Food
{
public:
    CeleryBrains();

    virtual void draw();
    virtual void erase();
    virtual void move();
};

#endif
