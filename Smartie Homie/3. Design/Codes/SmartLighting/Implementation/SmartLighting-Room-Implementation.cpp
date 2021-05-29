#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

#define off 0
#define on 1

#define idle 0
#define roomLighting 1
#define partyMode 2

//Code for room lighting
int state = idle;
int lightOutput = off;      //Light on/off
int toggle = off;           //Light toggle On/Off
int partyToggle = off;      //Party Mode toggle on/off
int timerMode = off;        //Timer mode on/off
int desiredTime = 0;        //Timer input
int sleeptime = 0;          //Time sleep until timer runs out


void checkForInput(int &toggle, int &partyToggle, int &state)
{
    cout << "Would you like keep the light on? Yes (1), No (0): " << endl;     //
    cin >> toggle;                                                      //store the input
    if (!toggle)                                                       
    {                                                                   //
        partyToggle = off;                                              // -> reset partyToggle
        state = idle;                                                   // -> change state to idle (off)
    }
    else                                                                //
    {
        cout << "Light is on" << endl;
        cout << "Would you like to keep party mode on? Yes (1), No (0): " << endl;   //ask if party mode will be turned off or not
        cin >> partyToggle;                                                             //store input for partyToggle
        if (!partyToggle)                                                              
        {
            state = roomLighting;                                                       //-> change state to normal room lighting
        }
        else cout << "Light is blinking in disco mode!" << endl;
    }
}

void toggleModeFunct(int &state, int &toggle)
{
    while(toggle)                                                           //while light is on
    {
        cout << "Would you like to keep the light on? Yes (1), No (0): " << endl;
        cin>>toggle;                                                        //input value for toggle
    }
    if(!toggle)                                                             //if toggle value is 0
    {
        state = idle;                                                       //change state to idle (light off)
    }
}

int modeSelect(int &timerMode, int &desiredTime)
{
    cout << "Please choose timer mode on (1) or off (0): " << endl;
    cin >> timerMode;                                                               //input timer mode (1: on, 0: off)
    if(timerMode)
    {                                                                               //if timer mode is on
        cout << "Please enter desired time in minutes: " << endl;
        cin >> desiredTime;
        return desiredTime;                                                         //insert timer number
    }
}

void timerModeFunct(int &desiredTime, int &state, int &timerMode, int &sleeptime)
{
    sleeptime = desiredTime * 60000;                    //Minutes to Miliseconds conversion
    Sleep(sleeptime);									//sleep the control unit for inserted amount of time		
    state = idle;                                       //when it wakes up, change state to idle (turn off light)
    timerMode = off;                                    //timer mode reset
}

void turnOnLight(int &lightOutput)
{
    lightOutput = on;
    cout << "Light is on" << endl; 
}

void turnOffLight(int &lightOutput)
{
    lightOutput = off;
    cout << "Light is off" << endl;
}

void waitForToggle(int &toggle, int &partyToggle)
{
	cout << "Please enter 1 to turn on light: " << endl;
    cin >> toggle;                                                   //input for toggle and party toggle
    cout << "Please enter 1 to turn on party mode: " << endl;
    cin >> partyToggle;
}

int main()
{
    for (int i = 0; i < 10; i++)
    {
    switch (state)
    {
    case idle:														//State: Room light idle (off)
        turnOffLight(lightOutput);
        waitForToggle(toggle, partyToggle);
        if(toggle&&partyToggle)                                                         //if toggle is 1 and partyToggle is 1
        {
        state = partyMode;  
        
        }
        else if(toggle && !partyToggle)                                                 //if toggle is 1 and partyToggle is 0
        {
        state = roomLighting;                                                       //go back to normal lighting state
        }
        break;

    case roomLighting:												//State: room lighting
        turnOnLight(lightOutput);
        modeSelect(timerMode, desiredTime);
        if(timerMode)
        {
            timerModeFunct(desiredTime, state, timerMode, sleeptime);
        }
        else
        {
            toggleModeFunct(state, toggle);
        }
        break;

    case partyMode:													//State: party mode
        turnOnLight(lightOutput);
        cout << "Party Mode on" << endl;
        cout << "Light is blinking in disco mode!" << endl;
        while(partyToggle)
        {
            checkForInput(toggle, partyToggle, state);
        }
        break;
    }
    }
    return 0;
}
