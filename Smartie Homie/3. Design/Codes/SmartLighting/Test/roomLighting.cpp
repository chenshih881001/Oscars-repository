#ifndef ROOMLIGHTING_CPP
#define ROOMLIGHTING_CPP

#define off 0
#define on 1

#define idle 0
#define roomLighting 1
#define partyMode 2

#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>
#include <windows.h>

using namespace std;


//modified function for testing


int checkForInput(int &toggle, int &partyToggle, int &state)
{
    toggle = !toggle;
    if (!toggle)
    {
        partyToggle = off;
        state = idle;
    }

    else
    {
        partyToggle = !partyToggle;
        if (!partyToggle)
        {
            state = roomLighting;
        }
    }
    return toggle, partyToggle, state;
}


void toggleModeFunct(int &state, int &toggle)
{
    while(toggle)
    {
        toggle = rand() % 2;                            //randomize toggle value instead of input
    }
    if(!toggle)
    {
        state = idle;
    }
}

void timerModeFunct(int &desiredTime, int &state, int &timerMode, int &sleeptime)
{
    sleeptime = desiredTime * 60000;                    //Minutes to Miliseconds conversion
    Sleep(sleeptime);											
    state = idle;
    timerMode = off;
}

void turnOnLight(int &lightOutput)
{
    lightOutput = on;
}

void waitForToggle(int &toggle, int &partyToggle, int &state)
{
    if(toggle&&partyToggle)
    {
        state = partyMode;
    }
    else if(toggle && !partyToggle)
    {
        state = roomLighting;
    }
}

void turnOffLight(int &lightOutput)
{
    lightOutput = off;
}

#endif
