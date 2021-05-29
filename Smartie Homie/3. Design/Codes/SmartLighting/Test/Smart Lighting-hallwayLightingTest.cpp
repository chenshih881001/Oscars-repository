#include <iostream>
#include <time.h>
#include <windows.h>
#include "hallwayLighting.cpp"    

using namespace std;

#define off 0
#define on 1

#define monitoring 1
#define hallwayLighting 2
#define off 0


#define testFailed 0
#define testPassed 1

//Code for hallway lighting test

int state = off;
int humanDetected = 0;
int movementDetected = 0;
int hallwayLightOutput = 0;
int height = 0;
int testResult = testPassed;


int lookForMovementTest(int &testResult, int &movementDetected, int &height, int &state)
{
    for (int i=0; i<10; i++)                   //run test 10 times
    {
        lookForMovement(movementDetected, height, state);
        if (!movementDetected && state != off)
        {
            cout << "Error Code 1: State does not change to off when there's no movement" << endl;
            testResult = testFailed;
        }   
    }
    return testResult;
}

int cameraHumanCheckTest(int &testResult, int &humanDetected, int &height, int &state)
{
    for (int i=0; i<10; i++)
    {
        cameraHumanCheck(humanDetected, height, state);
        if(humanDetected && state != hallwayLighting)
        {
            cout << "Error Code 2: Light is not on when human is detected" << endl;
            testResult = testFailed; 
        }
    }
    return testResult;
}

int turnoffLightTest(int &testResult, int &hallwayLightOutput, int &state)
{
        for (int i=0; i<10; i++)
        {
            turnoffLight(hallwayLightOutput, state);
			if (hallwayLightOutput)
            {
                cout << "Error Code 3: light does not turn off" << endl;
                testResult = testFailed;
            }
            else if (!hallwayLightOutput && state != monitoring)
            {
                cout << "Error Code 4: state does not change when light is off" << endl;
                testResult = testFailed;
            }
        }
        return testResult;
}

int turnonHallwayLightTest(int &hallwayLightOutput, int &height, int &state, int &testResult)
{
        for (int i=0; i<10; i++)
        {
            turnonHallwayLight(hallwayLightOutput, height, state);
			if (!hallwayLightOutput)
            {
                cout << "Error Code 5: light does not turn on" << endl;
                testResult = testFailed;
            }
            else if (height != 0)
            {
                cout << "Error Code 6: Height value does not reset" << endl;
                testResult = testFailed;    
            }
            else if (hallwayLightOutput && state != monitoring)
            {
                cout << "Error Code 7: State does not change at the end of operation" << endl;
                testResult = testFailed;                    
            }
        }
}


int main()
{
    lookForMovementTest(testResult, movementDetected, height, state);
    cameraHumanCheckTest(testResult, humanDetected, height, state);
    turnoffLightTest(testResult, hallwayLightOutput, state);
    turnonHallwayLightTest(hallwayLightOutput, height,state, testResult);

        if (testResult == testPassed)                                               //if all tests are passed
        {
        cout << "Congrats, test passed! " << endl;
        }
        if (testResult == testFailed)                                                   //if any test is not passed
        {
        cout << "You did not pass" << endl;
        }
    return testResult;
}

