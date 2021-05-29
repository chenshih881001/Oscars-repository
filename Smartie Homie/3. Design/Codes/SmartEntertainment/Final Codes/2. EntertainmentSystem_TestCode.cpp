#include <iostream>
#include "Entertainment.h"
#include <math.h>
#include <cstdlib>

using namespace std;

#define testFailed 0
#define testPassed 1

int state = idle;
int censorEnabled = off;
int eventMode = off;
int immersiveMode = off;
char **userInfo;
char **participantInfo;
int chosenEntertainment = 0;
int chosenProgram = 0;
char **programs;
int toggleInput = 0;
char *userID;
char *userPW;
int userAge;
char *userName;
char userGender; 
int loginState = 0;
int lightOutput = 0;
int airOutput = 0;
int musicPlayer = 0; 
int TV = 0;
int moviePlayer = 0;

int testResult = testPassed;

void waitForInputToggleTest(int &toggleInput, int &state, int &testResult)
{
	for (int i = 0; i < 10; i++)
	{
		toggleInput = rand() % 2;
		waitForInputToggle(toggleInput, state);
		if (toggleInput && state != login)
		{
			cout << "Error code 1 : login state not reached" << endl;
			testResult = testFailed;
		}
	}
}

void censorAdultMaterialTest(int &censorEnabled, int &testResult)
{
	for (int i = 0; i < 10; i++)
	{
		censorAdultMaterial(censorEnabled);
		if (censorEnabled == 0)
		{
			cout << "Error Code 2 : material not censored" << endl;
			testResult = testFailed;
		}
	}
}

void loginSuccessfulTest(int &loginState, int &state, int &testResult)
{
	for (int i = 0; i < 10; i++)
	{
		loginState = rand() % 2;
		loginSuccessful(loginState, state);
		if (loginState = state != chooseEntertainment)
		{
			cout << "Error Code 3 : chooseEntertainment state not reached" << endl;
			testResult = testFailed;
		}
	}
}

void chooseProgramsTest(int &chosenEntertainment, int &chosenProgram, int &state, char **&programs, int &testResult)
{
	for (int i = 0; i < 10; i++)
	{
		choosePrograms(chosenEntertainment, chosenProgram, state, programs);
		if (state != active)
		{
			cout << "Error Code 4 : active state not reached" << endl;
			testResult = testFailed;
		}
	}
}

void turnOnDeviceTest(int &chosenEntertainment, int &testResult, int &TV, int &moviePlayer, int &musicPlayer) 
{
	for (int i = 0; i < 10; i++)
	{
		chosenEntertainment = rand() % 2; 
		turnOnDevice(chosenEntertainment, TV, moviePlayer, musicPlayer);
		if (!TV)
		{
			cout << "Error Code 5 : TV off" << endl;
			testResult = testFailed;
		}
		if (chosenEntertainment == 1 && !moviePlayer)
		{
			cout << "Error Code 6 : Movie Player not ready" << endl; 
			testResult = testFailed;
		}
		if (chosenEntertainment == 2 && !musicPlayer)
		{
			cout << "Error Code 7 : Music Player not ready" << endl;
			testResult = testFailed;
		}
	}
}

void immersiveLightTest(int &lightOutput, int &testResult)
{
	for (int i = 0; i < 10; i++)
	{
		immersiveLight(lightOutput);
		if (lightOutput == 0)
		{
			cout << "Error Code 8 : immersive light not functioning" << endl;
			testResult = testFailed;
		}
	}
}

void immersiveAirTest(int &airOutput, int &testResult)
{
	for (int i = 0; i < 10; i++)
	{
		immersiveAir(airOutput);
		if (airOutput == 0)
		{
			cout << "Error Code 9 : immersive air not functioning" << endl;
			testResult = testFailed;
		}
	}
}

int main()
{
	waitForInputToggleTest(toggleInput, state, testResult);
	censorAdultMaterialTest(censorEnabled, testResult);
	loginSuccessfulTest(loginState, state, testResult);
	chooseProgramsTest(chosenEntertainment, chosenProgram, state, programs, testResult);
	turnOnDeviceTest(chosenEntertainment, testResult, TV, moviePlayer, musicPlayer);
	immersiveLightTest(lightOutput, testResult);
	immersiveAirTest(airOutput, testResult);
	if (testResult)
		cout << "All tests passed" << endl;
	else
		cout << "Test failed" << endl;
	return testResult;
}
