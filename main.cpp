#include "mbed.h"
#include "uLCD_4DGL.h"
#include "speaker.h"
#include "joystick.h"
#include "gameJingle.h"
#include "screenObject.h"
#include "celeryBrains.h"
#include "meanGreenBeans.h"
#include "macaroniMush.h"
#include "pecanPinkie.h"
#include "zombiePoisonPill.h"
#include "gobbleBuzz.h"
#include "sentientPoisonPill.h"


uLCD_4DGL uLCD(p9, p10, p11);
Speaker    mySpeaker(p25);
Nav_Switch myNav(p16, p13, p14, p12, p15);

DigitalIn pb1(p21); // slow
DigitalIn pb2(p22); // fast
DigitalIn pb3(p23); // invert colors
DigitalIn pb4(p24); // pause/resume


bool colorsInverted = false;
int  npcSpeedFactor = 2;   // default Food/Poison speed multiplier

#define _ BLACK
#define X BROWN
#define R RED
#define Y YELLOW

// Game Bounds
#define SCREEN_LEFT   2
#define SCREEN_RIGHT 118
#define SCREEN_TOP    2
#define SCREEN_BOTTOM 108

#define TURKEY_WIDTH  11
#define TURKEY_HEIGHT  8

//TurkeySprite
int turkeySpriteOriginal[TURKEY_WIDTH * TURKEY_HEIGHT] = {
    _,_,_,_,X,X,X,R,R,_,_,
    _,X,X,X,X,X,X,X,R,Y,_,
    X,X,X,X,X,_,_,X,X,Y,Y,
    X,X,X,X,X,_,_,X,X,Y,_,
    X,X,X,X,X,X,X,X,R,R,R,
    _,_,_,X,X,_,X,X,_,_,_,
    _,_,X,X,_,_,_,X,X,_,_,
    X,X,_,_,_,X,_,_,_,X,X
};

// This is what BLIT actually uses
int turkeySpriteCurrent[TURKEY_WIDTH * TURKEY_HEIGHT];

//Created in GLobal so sentientPoisonPill can access
GobbleBuzz turkey;


// Color inversion mapping
int invertColor(int c)
{
    if (c == BLACK)  return WHITE;
    if (c == WHITE)  return BLACK;
    if (c == RED)    return BLUE;
    if (c == BLUE)   return RED;
    if (c == YELLOW) return BROWN;
    if (c == BROWN)  return GREEN;
    if (c == GREEN)  return YELLOW;
    if (c == LGREY)  return DGREY;
    if (c == DGREY)  return LGREY;
    return c;
}

int mapColor(int baseColor)
{
    if (!colorsInverted) return baseColor;
    return invertColor(baseColor);
}

int getColor(int baseColor)
{
    return mapColor(baseColor);
}

// Update turkeySpriteCurrent from ORIGINAL + current inversion state
void updateTurkeySprite()
{
    int i;
    for (i = 0; i < TURKEY_WIDTH * TURKEY_HEIGHT; i++) {
        int base = turkeySpriteOriginal[i];
        turkeySpriteCurrent[i] = mapColor(base);
    }
}


// win / lose jingles
void playWinJingle()
{
    mySpeaker.PlayNote(523.25f, 0.15f, 0.3f); // C5
    mySpeaker.PlayNote(659.25f, 0.15f, 0.3f); // E5
    mySpeaker.PlayNote(783.99f, 0.25f, 0.3f); // G5
}

void playLoseJingle()
{
    mySpeaker.PlayNote(392.00f, 0.25f, 0.3f); // G4
    mySpeaker.PlayNote(261.63f, 0.35f, 0.3f); // C4
}



int main()
{
    srand(time(0));

    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    pb4.mode(PullUp);

    wait(0.3f);

    uLCD.baudrate(300000);
    wait(0.3f);

    // initial colors
    colorsInverted = false;
    updateTurkeySprite();

    // intro screen + jingle
    GameJingle jingle;
    uLCD.cls();
    jingle.playIntro();

    // create edibles
    const int OBJ_COUNT = 6;
    ScreenObject* objs[OBJ_COUNT];

    objs[0] = new CeleryBrains();
    objs[1] = new MeanGreenBeans();
    objs[2] = new MacaroniMush();
    objs[3] = new PecanPinkie();
    objs[4] = new ZombiePoisonPill();
    objs[5] = new SentientPoisonPill();

    int score       = 0;
    bool paused     = false;

    while (1) {

        // pb1: slow NPCs
        if (!pb1) npcSpeedFactor = 1;
        // pb2: fast NPCs
        if (!pb2) npcSpeedFactor = 3;
        // if neither pressed, keep default 2
        if (pb1 && pb2) npcSpeedFactor = 2;

        // pb3: invert colors for everything (including turkey)
        if (!pb3) {
            colorsInverted = !colorsInverted;
            updateTurkeySprite();
            wait(0.25f); // debounce
        }

        // pb4: pause / resume
        if (!pb4) {
            paused = !paused;
            wait(0.25f); // debounce
        }

        // movement
        turkey.erase();
        int i;
        for (i = 0; i < OBJ_COUNT; i++) {
            objs[i]->erase();
        }

        if (!paused) {
            turkey.move();

            for (i = 0; i < OBJ_COUNT; i++) {
                objs[i]->move();
            }
        }

        uLCD.filled_rectangle(0, 0, 127, 127, getColor(BLACK)); // background
        uLCD.rectangle(0, 0, 120, 110, getColor(GREEN));        // green border

        // DRAW turkey
        uLCD.BLIT(turkey.getXPos(), turkey.getYPos(),
                  TURKEY_WIDTH, TURKEY_HEIGHT,
                  turkeySpriteCurrent);

        // DRAW NPC objects
        for (i = 0; i < OBJ_COUNT; i++) {
            objs[i]->draw();
        }

        // Collision Handling
        for (i = 0; i < OBJ_COUNT; i++) {

            int ox = objs[i]->getX();
            int oy = objs[i]->getY();
            int ow = objs[i]->getWidth();
            int oh = objs[i]->getHeight();

            if (turkey.overlap(ox, oy, ox + ow, oy + oh)) {

                if (objs[i]->isPoison()) {
                    // POISON hit: lose a life
                    score = score - 10;

                    objs[i]->placeRandom();

                    if (score <= 0) {
                        uLCD.cls();
                        uLCD.printf("\n\n\n  Buzz died from \n       poison \n\n     YOU LOSE");
                        playLoseJingle();
                        while (1) { /* halt */ }
                    }
                } else {
                    // FOOD hit: add points from object
                    int delta = objs[i]->getScoreDelta();
                    score += delta;

                    objs[i]->placeRandom();

                    if (score >= 50) {
                        uLCD.cls();
                        uLCD.printf("\n\n\n   Buzz is full\n\n     YOU WIN");
                        playWinJingle();
                        while (1) { /* halt */ }
                    }
                }
            }
        }


        // HUD (score)
        uLCD.locate(0, 14);
        uLCD.text_width(1);
        uLCD.text_height(1);
        uLCD.printf("Score:%2d", score);

        // smooth motion
        wait(0.10f);
    }
}