#ifndef MEAN_GREEN_BEANS_H
#define MEAN_GREEN_BEANS_H

#include "screenObject.h"

extern int npcSpeedFactor;

class MeanGreenBeans : public Food
{
public:
    MeanGreenBeans();

    virtual void draw();
    virtual void erase();
    virtual void move();
};

#endif
