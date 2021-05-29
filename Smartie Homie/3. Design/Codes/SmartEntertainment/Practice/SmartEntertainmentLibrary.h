#include<iostream>
using namespace std;

const int IdleState = 0;
const int ActivedState = 1;
const int DoorOpen = 2;
const int IntruderAlarm = 3;
const int CameraAlarmIdle = 4;

/*-------------------------------------------------------------------*/
int CheckSwitch(int Switch)
{
    while(Switch != 0 && Switch != 1)
    {
        cout << ">> Please enter valid command: ";
        cin >> Switch;
    }
    if(Switch == 1)
        return ActivedState;
    else
        return IdleState;
}
/*-------------------------------------------------------------------*/
int idle(int Switch)
{
    while(Switch != 1)
    {
        cout << ">> Please enter valid command: ";
        cin >> Switch;
    }
    return ActivedState;
}
/*-------------------------------------------------------------------*/
int CheckMotion(int motion)
{
    while(motion != 1 && motion !=0)
    {
        cout << ">> Please enter valid command: ";
        cin >> motion;
    }
    if(motion == 1)
        return 1;
    else
        return 0;
}
/*-------------------------------------------------------------------*/
int CheckUserConfirmation(int UserConfirmation)
{
    if(UserConfirmation != 1 && UserConfirmation != 0)
        cout << ">> Please enter valid command: " << endl;
    else if(UserConfirmation == 1)
        return DoorOpen;
    else
        return IntruderAlarm;
}
/*-------------------------------------------------------------------*/
void Number(int Try)
{
    if(Try == 0)
        cout << ">> second attempt: ";
    if(Try == 1)
        cout << ">> third attempt: ";
}
/*-------------------------------------------------------------------*/
int CheckReset(int reset)
{
    if(reset != 1 && reset != 0)
        cout << "Please enter valid command: ";
    else if(reset == 1)
        return ActivedState;
    else if(reset != 1 && reset != 0)
        cout << "Please enter valid command: " << endl;
    else if(reset == 1)
        return ActivedState;
    else
        return IdleState;
}


/*-------------------------------------------------------------------*/
void statement1()
{
    cout << "       Welcome to Smart Security System" << endl;
    cout << "__________________________________________________" << endl;
    cout << ">> Please create a password: ";
}
/*-------------------------------------------------------------------*/
void statement2()
{
    cout << ">> Enter 1 to turn ON / 0 to turn OFF: ";
}
/*-------------------------------------------------------------------*/
void statement3()
{
    cout << "\n";
    cout << ">> Security System is idle now" << endl;
    cout << ">> Enter 1 to start: ";
}
/*-------------------------------------------------------------------*/
void statement4()
{
    cout << "\n";
    cout << ">> Security System: ON" << endl;
}
/*-------------------------------------------------------------------*/
void statement5()
{
    cout << "\n";
    cout << ">> Camera & Alarm are now idle" << endl;
    cout << ">> Would you like to enter the house?" << endl;
    cout << ">> Enter 1 to accept / 0 to decline: ";
}
/*-------------------------------------------------------------------*/
void statement6()
{
    cout << "\n";
    cout << ">> Camera starts recording! " << endl;
    cout << ">> Please enter password: ";
}
/*-------------------------------------------------------------------*/
void statement7()
{
    cout << "\n";
    cout << "[UserPhone] Someone attempted to enter the house, please confirm" << endl;
    cout << ">> Enter 1 to confirm / Enter 0 to report: ";
}
/*-------------------------------------------------------------------*/
void statement8()
{
    cout << "\n";
    cout << ">> Door is now unlocked, Welcome home" << endl;
}
/*-------------------------------------------------------------------*/
void statement9()
{
    cout << "\n";
    cout << ">> Would you like to reset the system?" << endl;
    cout << ">> Enter 1 to rest/ 0 to go back to idle mode: ";
}
/*-------------------------------------------------------------------*/
void statement10()
{
    cout << "\n";
    cout << "[Speaker] LEAVE! LEAVE! Police will arrive in 3 minutes!" << endl;
    cout << "\n";
    cout << ">> Would you like to reset the system?" << endl;
    cout << ">> Enter 1 to rest/ 0 to go back to idle mode: ";

}
/*-------------------------------------------------------------------*/
