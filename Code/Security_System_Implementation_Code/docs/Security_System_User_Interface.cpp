#include <iostream>
#include <string.h>
#include "SecuritySystemFunctionLibrary.h"
using namespace std;

#define IdleState 0
#define ActivedState 1
#define DoorOpen 2
#define IntruderAlarm 3
#define CameraAlarmIdle 4


int n = 0;
int state = 0;
int Switch;
int motion = 0;
int Try = 0;
int UserConfirmation = 0;
int reset = 0;
char SetPassword[15],GetPassword[15];
int CC = 0;

int main()
{
    statement1();
    cin >> SetPassword;
    int temp = strlen(SetPassword);
    statement2();
    cin >> Switch;
    state = CheckSwitch(Switch);

    while(n==0)
    {
        switch(state)
        {
        case IdleState:
        {
            statement3();
            cin >> Switch;
            state = idle(Switch);
            break;
        }

        case ActivedState:
        {
            statement4();
            state = CameraAlarmIdle;
            break;
        }

        case CameraAlarmIdle:
        {
            statement5(); //Camera & Alarm are now idle. Would you like to enter the house?
            cin >> motion;
            CC = CheckMotion(motion);
            if(CC == 0)
                state = CameraAlarmIdle;
            else
            {
                statement6();
                while(Try<3)
                {
                    cin >> GetPassword;
                    int i = 0,flag = 0;
                    for(i=0; i<temp; i++)
                    {
                        if(SetPassword[i]!= GetPassword[i])
                            flag++;
                    }
                    if(flag!=0)
                    {
                        Number(Try);
                        Try++;
                    }
                    else
                        Try = 4;
                }
                if(Try == 4)
                    state = DoorOpen;
                else
                {
                    statement7();
                    cin >> UserConfirmation;
                    state = CheckUserConfirmation(UserConfirmation);
                }
            }
            break;
        }
        case DoorOpen:
        {
            statement8();
            statement9();
            cin >> reset;
            state = CheckReset(reset);
            break;
        }
        case IntruderAlarm:
        {
            statement10();
            cin >> reset;
            state = CheckReset(reset);
            break;
        }
        }
    }
    return 0;
}
