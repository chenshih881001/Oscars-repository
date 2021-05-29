#ifndef HALLWAYLIGHTING_CPP
#define HALLWAYLIGHTING_CPP

#define off 0
#define on 1

#define monitoring 1
#define hallwayLighting 2
#define off 0

#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>
#include <windows.h>

using namespace std;


//modified function for testing


void lookForMovement(int &movementDetected, int &height, int &state)
{
    movementDetected = rand() % 2; 
    if(movementDetected)
    {
        height = rand() % 200;
    }
    else
    {
        state = off;      
    }                                 
}

void cameraHumanCheck(int &humanDetected, int &height, int &state)
{
    if(100<height)  																	
    {
        humanDetected = 1;
        state = hallwayLighting;
    }
}

void turnoffLight(int &hallwayLightOutput, int &state)
{
    hallwayLightOutput = 0;
    state = monitoring; 
}

void turnonHallwayLight(int &hallwayLightOutput, int &height, int &state)
{
    hallwayLightOutput = 1;
    Sleep(1000);                           // quicker delay for quicker testing
    height = 0;
    state = monitoring;
}

#endif
