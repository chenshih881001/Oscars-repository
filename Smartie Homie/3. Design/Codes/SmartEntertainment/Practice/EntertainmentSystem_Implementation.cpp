#include <iostream>
#include <cstdlib>
#include "EntertainmentSystemTest.h"
using namespace std;

int i;                                     // for the loop
int Min1 = 7, Max1 = 85;                   // range of the age
int Min2 = 1, Max2 = 3;                    // programs
int Min3 = 0, Max3 = 1;                    // immersive mode
int age;
int AdultContent = 0;
int ProgramSelect = 0, ProgramOutput = 0;
int ImmersiveModeSwitch = 0, ImmersiveModeOutput = 0;
int Switch = 0;
int state = 0;


int main()
{
    for(i=0;i<100;i++)
    {
        age = rand()%(Max1-Min1+1)+Min1;
        ProgramSelect = rand()%(Max2-Min2+1)+Min2;
        ImmersiveModeSwitch = rand()%(Max3-Min3+1)+Min3;
		Switch = rand()%(Max3-Min3+1)+Min3;
		
		if(Switch==1)
			state = 1;
		else
			state = 0;
			 
        if(age<18)
        {
            AdultContent = 0;
            if(ProgramSelect == 1)
                ProgramOutput = 1;
            if(ProgramSelect == 2)
                ProgramOutput = 2;
            if(ProgramSelect == 3)
                ProgramOutput = 3;
        }
        else
        {
            AdultContent = 1;
            if(ProgramSelect == 1)
                ProgramOutput = 1;
            if(ProgramSelect == 2)
                ProgramOutput = 2;
            if(ProgramSelect == 3)
                ProgramOutput = 3;
        }
        if(ImmersiveModeSwitch == 1)
            ImmersiveModeOutput = 1;
        else
            ImmersiveModeOutput = 0;

        cout << "test " << i+1 << endl;
        EntertainmentSystemTest(Switch,state,age,AdultContent,ProgramSelect,ProgramOutput,ImmersiveModeSwitch,ImmersiveModeOutput);
        cout << "----------------------" << endl;
    }
    return 0;
}
