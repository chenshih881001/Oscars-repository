#include <iostream>

using namespace std;

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
#define musicPlayer 3


int state = idle;
int censorEnabled = off;
int eventMode = off;
int immersiveMode = off;
char** userInfo;
char** participantInfo;
int chosenEntertainment = 0;
int chosenProgram = 0;
char** programs;
int toggleInput = 0;
char* userID;
char* userPW;
char** 
int userAge;
char* userName;
char userGender; // it can be m or f
int loginState = 0;
int lightOutput = 0;
int airOutput = 0;

int musicPlayer;
int TV;
int moviePlayer;

void waitForInputToggleFunction(int toggleInput,int state){
	cin >> toggleInput;
	if (toggleInput){
		state = login;
	}
}

void requestLogin(char* &userID,char* &userPW, int &loginState){
	cout << "Enter ID and Password";
	cin >> userID >> userPW;
	verifyLoginInfo(userID,userPW,loginState);
}

void verifyLoginInfo(char* userID,char* userPW, int &loginState)

void accessUserInfo(int &userAge, char* &userName,char &userGender){
	cin >> userAge >> userName >> userGender;
}

void eventModeToggleFunction(int &eventMode){
	cin >> eventMode;
}

void requestParticipantInfo(char** &participantInfo){
	cin >> particpantInfo;
}

void censorAdultMaterial(int censorEnabled){
	censorEnabled = 1;
}

void loginSuccessful(int loginState){
	if (loginState)
	state = chooseEntertainment;
}
	
void loadRecommendablePrograms(int censorEnabled,int eventMode,char** userInfo,char** participantInfo,char ** &programs)
{	if (censorEnabled)
	loadChildPrograms(userInfo,programs);
	
	if (eventMode)
	loadEventPrograms(userInfo,participantInfo,programs);
	
	else 
	loadNormalPrograms(userInfo,programs)
}

void choosePrograms(int &chosenEntertainment,int &chosenProgram,int &state,char** &programs)
{
	cout << "choose your entertainment type: 1 for movie, 2 for music, 3 for tvProgram" ;
	cin >> chosenEntertainment;
	filterProgram(chosenEntertainment);
	cout << "please choose from the followings"<<programs;
	cin >> chosenProgram;
	state = active;
}

<NOT COMPLETED YET>
void turnOnDevice(int chosenEntertainment){
	TV = on;
	if (chosenEntertainment == 1)
		moviePlayer = on;
	if (chosenentertainment == 2)
		musicPlayer = on;
	
}

void playProgram(int chosenProgram);

void immersiveModeToggleFunction(int &immersiveMode){
	cin >> immsersiveMode;
}

void immersiveLight(int &lightOutput){
	lightOutput = 1;
}

void immersiveAir(int &airOutput){
	airOutput = 1;
}

int main(){
	
	switch (state){
		
		case idle:
			waitForInputToggleFunction(toggleInput);
				
		case login:
			requestLogin(userID,userPW,loginState);
			accessUserInfo(userAge,userName,userGender);
			eventModeToggleFunction(eventMode);
			if (eventMode){
				requestParticipantInfo(participantInfo);
			}
			if (age<18){
				censorAdultMaterial(censorEnabled);
			}
			loginSuccessful(loginState);
			break;
	
		case chooseEntertainment: 
			loadRecommendablePrograms(censorEnabled,eventMode,userInfo,participantInfo,programs);
			choosePrograms(chosenEntertainment,chosenProgram,state,programs);
			break;
		
		case active:
			turnOnDevice(device);
			playProgram(play);
			immersiveModeToggleFunction(immersiveMode);
			if (immersiveMode){
				immersiveLight(lightOutput)
				immersiveAir(airOutput)
			}
			break;
		
	}
}
