#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;

#define IdleState 0
#define LoginState 1
#define ChooseEntertainmentState 2
#define ActiveState 3

#define movie 1
#define music 2
#define tvProgram 3

#define smartPhone 1
#define smartTV 2
#define musicPlayer 3


int n = 0;
int state = IdleState;
int Input;
int userAge;
int Switch;
int eventMode = 0;
int immersiveMode = 0;

void wakeUpFunction()
{
	cout << "Welcome to Smart Entertainment System" << endl;
	cout <<"___________________________________________" << endl;
	cout << "press 1 to start" << endl;
	cin >> Input;
	if (Input == 1)                                                     
		state = LoginState;
	else {
		cout << "\nSmart Entertainment System Standby" << endl;
		state = IdleState;
	}
}

void censorFunction()
{	
	cout << "\nEnter your age" << endl;
	cin >> userAge;	
	if (userAge<18)
		cout << "Inappropriate materials are censored" << endl;
	else 
		cout << "Censor not executed" << endl;
}

void eventFunction()
{
	cout << "\nDo you have any minor members in your group?" << endl;
	cout << "if yes, press 1" << endl;
	cin >> Input;
	if (Input == 1)
		cout << "Inappropriate materials are censored" << endl;
	else {
		cout << "Censor not executed" << endl;
	}
	cout << "\nLogin Successful" << endl;
	state = ChooseEntertainmentState;
}

void chooseDeviceFunction()
{
	cout << "\nChoose the device you wish to play your contents on" << endl;
	cout << "Press 1 for your smartphone, press 2 for smart TV, or press 3 for music player" << endl;
	cin >> Input;
	if (Input == 1)
		cout << "\nSmartphone is on" << endl;
	else if (Input == 2)
		cout << "\nSmart TV is on" << endl;
	else if (Input == 3)
		cout << "\nMusic player is on" << endl;						
}

void chooseContentsTypeFunction()
{
	cout << "\nChoose your contents type" << endl;
	cout << "Press 1 for movie, press 2 for music, or press 3 for TV Program" << endl;
	cin >> Input;
	if (Input == 1)
		cout << "\nLoading recommended movie lists on your device" << endl;
	else if (Input == 2)
		cout << "\nLoading recommended music playlists on your device" << endl;
	else if (Input == 3)
		cout << "\nLoading recommended TV programs on your device" << endl;					
	state = ActiveState;
}

void chooseProgramFunction()
{
	cout << "\nChoose your program from the list" << endl;
	cin >> Input;
	if (Input)
		cout << "\nYour chosen contents is now being played" << endl;	
}

void chooseImmersiveFunction()
{
	cout << "\nWould you like to initiate Immersive Mode?" << endl;
	cout << "Press 1 for yes" << endl;
	cin >> Input;
	if (Input == 1)
		cout << "\nImmersive mode activated" << endl;
	else 
		cout << "\nImmersive mode not activated" <<endl;
}

void completeMessage()
{
	cout << "\nProgram is being played" << endl;
	cout << "\n" << endl;
	state = IdleState;
}

int main()
{
	while (n==0){
		switch(state){
			case IdleState:
			{
				wakeUpFunction();
				break;
			}
			case LoginState:
			{
				censorFunction();
				eventFunction();
				break;
			}
			case ChooseEntertainmentState:
			{
				chooseDeviceFunction();
				chooseContentsTypeFunction();							
				break;
			}
			case ActiveState:
			{
				chooseProgramFunction();
				chooseImmersiveFunction();
				completeMessage();
				break;
			}
		}	
	}
	return 0;
}


