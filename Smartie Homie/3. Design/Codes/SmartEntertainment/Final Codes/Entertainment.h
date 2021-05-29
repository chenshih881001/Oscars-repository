#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#define on 1
#define off 0

#define idle 0
#define login 1
#define chooseEntertainment 2
#define active 3

#define movie 1
#define music 2
#define tvProgram 3

#define smartPhone 1
#define smartTV 2
#define musicPlay 3

//modified functions for testing

void waitForInputToggle(int &toggleInput, int &state)
{
	if (toggleInput)
	{
		state = login;
	}
}

void censorAdultMaterial(int &censorEnabled)
{
	censorEnabled = 1;
}

void loginSuccessful(int &loginState, int &state)
{
	if (loginState)
		state = chooseEntertainment;
}

void choosePrograms(int &chosenEntertainment, int &chosenProgram, int &state, char **&programs)
{
	state = active;
}

void turnOnDevice(int chosenEntertainment, int &TV, int &moviePlayer, int &musicPlayer) // loading is not &
{
	TV = on;
	if (chosenEntertainment == 1)
		moviePlayer = on;
	if (chosenEntertainment == 2)
		musicPlayer = on;
}

void immersiveLight(int &lightOutput)
{
	lightOutput = 1;
}

void immersiveAir(int &airOutput)
{
	airOutput = 1;
}

#endif
