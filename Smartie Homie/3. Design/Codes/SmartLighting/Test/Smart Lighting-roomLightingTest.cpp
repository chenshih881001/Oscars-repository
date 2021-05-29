#include <iostream>
#include <time.h>
#include <windows.h>
#include "roomLighting.cpp"                 //include functions for testing 

using namespace std;

#define off 0
#define on 1

#define idle 0
#define roomLighting 1
#define partyMode 2

#define testFailed 0
#define testPassed 1

int state = idle;

//Code for room lighting test

int lightOutput = off;
int toggle = off;
int partyToggle = off;
int timerMode = off;
int desiredTime = 0;
int sleeptime = 0;
int testResult = testPassed;


int checkForInputTest(int &testResult, int &toggle, int &partyToggle, int &state)
{
    for (int i=0; i<10; i++)                   //run test 10 times
    {
        int dummy_1 = rand() % 2;               //randomize 0 or 1 as dummy for flipping
        int dummy_2 = rand() % 2;
        toggle = dummy_1;                       //map toggle to dummy_1 to test for flipping later
        partyToggle = dummy_2;                  //map partyToggle to dummy_2 to test for flipping later
        
		checkForInput(toggle, partyToggle, state);      //call checkforInput function

        if(toggle == dummy_1)                   //if toggle is still dummy_1, it means the flipping code does not work                 
        {
            cout << "Error Code 1: toggle is not flipping "<< endl;
            testResult = testFailed;
        }
        if(!toggle)                             //if toggle is 0,  
        {
            if(partyToggle)                     //if partyToggle is 1         
            {
                cout << "Error Code 2: party toggle is not turning off" << endl;
                testResult = testFailed;
            }
            else if (state != idle)            //if state is not idle          
            {
                cout << "Error Code 3: state does not return to idle" << endl;
                testResult = testFailed;
            }
        }
        if(toggle)                              //if toggle is 1
        {
            if(partyToggle == dummy_2)          //if partyToggle does not flip 
            {
                cout << "Error Code 4: party toggle is not flipping" << endl;
                testResult = testFailed;
            }
            if(!partyToggle)                    //if partyToggle is 0
            {
                if(state != roomLighting)       //if state does not change to roomLighting (normal light)
                {
                    cout << "Error Code 5: state does not change to room lighting "<< endl;
                    testResult = testFailed;
                }
                if(partyToggle)                 //if partyToggle is 1
                {
                    if(state != partyMode)      //if state is not partyMode
                    {
                        cout << "Error Code 6: state is changing randomly" << endl;
                        testResult = testFailed;
                    }
                }
            }

        }
    }
    return testResult;
}

int turnOnLightTest (int &lightOutput, int &testResult)
{
        for (int i=0; i<10; i++)
        {
            turnOnLight(lightOutput);
			
            if (lightOutput == off){
                cout << "Error Code 7: light does not turn on" << endl;
                testResult = testFailed;
            }
        }
}

int turnOffLightTest (int &lightOutput, int &testResult)
{
        for (int i=0; i<10; i++)
        {
            turnOffLight(lightOutput);
			
            if (lightOutput == on){
                cout << "Error Code 8: light does not turn off" << endl;
                testResult = testFailed;
            }
        }
}

void timerModeFunctTest(int &desiredTime, int &state, int &timerMode, int &testResult, int &sleeptime)
{
    for (int i=0; i<1; i++)
    {
        desiredTime = rand() % 2;
        timerModeFunct(desiredTime, state, timerMode, sleeptime);

        if (state != idle){
            cout << "Error Code 9: state does not change to idle when timer runs out" << endl;
            testResult = testFailed;
        }
        if (timerMode != off){
            cout << "Error Code 10: Timer mode does not turn off at the end" << endl;
            testResult = testFailed;
        }
        if (sleeptime != desiredTime*60000){
            cout << "Error Code 11: Milliseconds conversion is not working" << endl;
            testResult = testFailed;
        }

    }
}

void toggleModeFunctTest(int &state, int &toggle, int &testResult)
{
    for (int i=0; i<10; i++)
    {
        toggleModeFunct(state, toggle);
        if (toggle && state != idle){
            cout << "Error Code 12: roomLighting State does not go back to idle" << endl;
            testResult = testFailed;
        }

    }
}

void waitForToggleTest(int &toggle, int &partyToggle, int &state, int &testResult)
{
    for (int i=0; i<10; i++)
    {
        toggle = rand() % 2;
        partyToggle = rand() % 2;
        waitForToggle(toggle, partyToggle, state);
        if (toggle && partyToggle && state != partyMode){
            cout << "Error Code 13: partyMode does not flip" << endl;
            testResult = testFailed;
        }
        else if (toggle && !partyToggle && state != roomLighting){
            cout << "Error Code 14: roomLight state does not flip" << endl;
            testResult = testFailed;
        }

    }
   
}

int main()
{
    checkForInputTest(testResult, toggle, partyToggle, state);
    turnOnLightTest (lightOutput, testResult);
    turnOffLightTest (lightOutput, testResult);
    timerModeFunctTest(desiredTime, state, timerMode, testResult, sleeptime);
    toggleModeFunctTest(state, toggle, testResult);
    waitForToggleTest(toggle, partyToggle, state, testResult);
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

