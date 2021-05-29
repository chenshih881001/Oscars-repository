#include <iostream>
using namespace std;
/*
error code 01: switch malfunction
error code 02: age identification error
error code 03: program output error
error code 04: immersive mode malfunction

*/
int flag = 0 ;

void EntertainmentSystemTest(int Switch,int state,int age,int AdultContent,int ProgramSelect,int ProgramOutput,int ImmersiveModeSwitch,int ImmersiveModeOutput)
{
	if(Switch == 1 && state == 0 ||Switch == 0 && state == 1)
		cout << "error code 01" << endl;
	else 
		flag++;
		
    if(age < 18 && AdultContent == 1 || age >= 18 && AdultContent == 0)
        cout << "error code 02" << endl;
    else
        flag++;

    if(ProgramSelect == 1 && ProgramOutput != 1)
        cout << "error code 03" << endl;
    else
        flag++;

    if(ProgramSelect == 2 && ProgramOutput != 2)
        cout << "error code 03" << endl;
    else
        flag++;

    if(ProgramSelect == 3 && ProgramOutput != 3)
        cout << "error code 03" << endl;
    else
        flag++;

    if(ImmersiveModeSwitch == 1 && ImmersiveModeOutput == 0  || ImmersiveModeSwitch == 0 && ImmersiveModeOutput == 1)
        cout << "error code 04" << endl;
    else
        flag++;

    if(flag > 0)
        cout << "Status: Pass" << endl;
}
