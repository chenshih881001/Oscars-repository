#include "windows.h"

#ifndef GRIDMON_H
#define GRIDMON_H

#define Monitoring 0
#define BatteryT 1
#define PanelT 2
#define PowerT 3
#define EmergencyMode 4
#define Panelreset 5
#define ServiceMode 6
#define EmergencyS 7

bool readBatteryStatus(); //returns true if battery is malfunctioning
bool readPanelStatus();   //returns true if solar panel is malfunctionsing
bool readGridStatus();    //returns true if home grid is malfunctionsing
bool readEmerStatus();    //returns true if there is an emergency situation
int getUserResponse();    //requests a simple [y/n] response from user
void checkstates();       //inputs individual issues into issue list
void movetostate();       //decides what process to follow for every issue
bool isitresolved();      //transforms user input to proper response
bool isitfalse();         //transforms user input to proper false alarm response
void loading();           //running process. delays a few seconds

//various print functions for each case
void printemergency();
void printdeepem();
void printservice();
void printdeepserv();
void monitor();
void batt();
void pant();
void emert();
void powt();
void panelres();

int count[4] = {}; //initialize issue list (if no issue found{0,0,0,0}, every issue{1,1,1,1})
int empty[4] = {}; //empty list to compare to
int state = Monitoring;
int x = 0;
int batstat, panstat, gridstat, emerstat;

bool readBatteryStatus()
{
    batstat = rand() % 2;
    return batstat;
}

bool readPanelStatus()
{
    panstat = rand() % 2;
    return panstat;
}

bool readGridStatus()
{
    gridstat = rand() % 2;
    return gridstat;
}

bool readEmerStatus()
{
    emerstat = rand() % 2;
    return emerstat;
}

void checkstates()
{
    if (readBatteryStatus())
        count[0] = 1;
    else
        count[0] = 0;
    if (readPanelStatus())
        count[1] = 1;
    else
        count[1] = 0;
    if (readGridStatus())
        count[2] = 1;
    else
        count[2] = 0;
    if (readEmerStatus())
        count[3] = 1;
    else
        count[3] = 0;
}

void movetostate()
{
    printf("Analyzing issues");
    loading();
    if (count[3] == 1)
    {
        printf("Emergency!!!\n");
        Sleep(600);
        state = EmergencyMode;
        count[3] = 0;
    }
    else if (count[0] == 1)
    {
        printf("Battery is faulty\n");
        Sleep(600);
        state = BatteryT;
        count[0] = 0;
    }
    else if (count[1] == 1)
    {
        printf("Solar Panel is faulty\n");
        Sleep(600);
        state = PanelT;
        count[1] = 0;
    }
    else if (count[2] == 1)
    {
        printf("Power Grid is faulty\n");
        Sleep(600);
        state = PowerT;
        count[2] = 0;
    }

    else if (std::equal(std::begin(count), std::end(count), std::begin(empty)))
    {
        printf("All issues resolved!\n");
        Sleep(1000);
        state = Monitoring;
        printf("Returning to Monitoring mode\n");
        Sleep(1000);
    }
}

int getUserResponse()
{
    char response;
    do
    {
        printf("[y/n]\n");
        cin >> ("%c", &response);
        if (!cin.fail() && response != 'y' && response != 'n')
            printf("Please enter a valid response\n");
    } while (!cin.fail() && response != 'y' && response != 'n');
    if (response == 'y')
        return 1;
    else
        return 0;
}

bool isitresolved()
{
    printf("Is the issue resolved?\n");
    return getUserResponse();
}

bool isitfalse()
{
    printf("Is it a false alarm?\n");
    return getUserResponse();
}

void loading()
{
    Sleep(400);
    printf(".");
    Sleep(400);
    printf(".");
    Sleep(400);
    printf(".\n");
}
void printemergency()
{
    printf("Emergency State Activated\n");
    printf("Contacting Authorities");
    loading();
}
void printdeepem()
{
    printf("Please follow Emergency Procedures");
    loading();
    Sleep(1000);
    printf("Emergency over. Analyzing damages");
    loading();
    movetostate();
}
void printservice()
{
    printf("System in Service Mode\n");
    printf("Contacting Authorized Service");
    loading();
}
void printdeepserv()
{
    printf("System in deep Service Mode\n");
    Sleep(1000);
    printf("Sending Maintenance Personnel");
    loading();
    printf("Repair in progress");
    loading();
    movetostate();
}

void monitor()
{
    checkstates();
    printf("Monitoring");
    loading();
    movetostate();
}

void batt()
{
    printf("Battery Troubleshooting");
    loading();
}
void pant()
{
    printf("Solar Panel Troubleshooting");
    loading();
}
void emert()
{
    printf("Detecting Emergency");
    loading();
}
void powt()
{
    printf("Power Grid Troubleshooting");
    loading();
}
void panelres()
{
    printf("Solar Panel System reseting\n");
    loading();
}

#endif