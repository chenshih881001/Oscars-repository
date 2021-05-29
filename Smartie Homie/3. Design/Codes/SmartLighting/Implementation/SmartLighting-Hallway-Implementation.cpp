#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

#define monitoring 1
#define hallwayLighting 2
#define off 0


int state = off;
int humanDetected = 0;
int movementDetected = 0;
int hallwayLightOutput = 0;
int height = 0;



void lookForMovement(int &movementDetected, int &height, int &state)
{
    cout << "Is movement detected? Yes (1), No (0)" << endl;
    cin >> movementDetected; 
    if(movementDetected)
    {
        cout << "Movement is detected." << endl; 
        cout << "Enter object's height: " << endl;
        cin >> height;
    }
    else
    {
        state = off;      
    }                                 
}


void cameraHumanCheck(int &humanDetected, int &height, int &state)
{
    if(100<height && height <250)  																	
    {
        cout << "Human is detected." << endl;
        humanDetected = 1;
        state = hallwayLighting;
    }
    else 
        {
        cout << "No human is found, light will stay off." << endl;
        }

}

void turnoffLight(int &hallwayLightOutput, int &state)
{
    hallwayLightOutput = 0;
    cout << "Hallway Light is off." << endl;
    state = monitoring; 
}

void turnonHallwayLight(int &hallwayLightOutput, int &height, int &state)
{
    hallwayLightOutput = 1;
    cout << "Hallway Light is on." << endl; 
    cout << "Please wait, light is on for 6 seconds." << endl; 
    Sleep(10000);                           //delay for 6 seconds
    height = 0;
    state = monitoring;
}

int main()                                  //Hallway Lighting
{
    for (int i = 0; i < 10; i++)
    {
    switch (state)
    {
    case off:
        turnoffLight(hallwayLightOutput, state);
        break;

    case monitoring:
        lookForMovement(movementDetected, height, state);
        cameraHumanCheck(humanDetected, height, state);
        break;

    case hallwayLighting:
        turnonHallwayLight(hallwayLightOutput, height, state);
        break;
    }
    }
    return 0;
}

