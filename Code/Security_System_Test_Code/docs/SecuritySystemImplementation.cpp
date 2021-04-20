#include <iostream>
#include <cstdlib>
#include "SecuritySystemTest.h"
using namespace std;

/*
error code 01: door malfunction
error code 02: alarm malfunction
error code 03: camera malfunction
*/

int Min = 0;
int Max = 1;
int i = 0;


int main()
{

    for(i = 0; i < 100  ; i++)
    {
        //idle state(default)
        int door = 1;   //DoorLocked:1  DoorUnlocked:0
        int alarm = 0;  //idle:0        activated:1
        int camera = 0; //idle:0        activated:1

        //random events
        int smoke = rand()%(Max-Min+1)+Min;            //detected:1   else:0
        int motion = rand()%(Max-Min+1)+Min;           //detected:1   else:0
        int ValidPassword = rand()%(Max-Min+1)+Min;    //valid:1      invalid:0
        int UserConfirmation = rand()%(Max-Min+1)+Min; //accept:1     decline:0

        if(motion == 1)
        {
            camera = 1;
            if(ValidPassword == 1)
                door = 0;
            else
            {
                if(UserConfirmation == 1)
                    door = 0;
                else
                    alarm = 1;
            }
        }

        if(smoke == 1)
        {
            door = 0;
            alarm = 1;
        }

        cout << "<test " << i+1 << ">" << endl;
        SecuritySystemTest(smoke,motion,door,camera,alarm,ValidPassword,UserConfirmation);
        //cout << smoke << motion << door << camera << alarm << ValidPassword << UserConfirmation << endl;
        //cout << flag << endl;
        cout << "---------------------\n";
    }
    return 0;
}
