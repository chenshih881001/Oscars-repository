#include <ctime>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include "devicemanager.h"

using namespace std;

int state = idle;
int devicePower = on;
int initialSetup = 0;
int userCount = 0;
int deviceCount = 0;
int loginStatus = 0;
int loggedInUser = 0;
int chosenDevice = 0;
int success = 0;

std::vector<user> userList;
std::vector<device> deviceList;
std::string activation;
std::string loggedInUserName;
std::string mode;

int main()
{
    srand(time(NULL));
    welcomeScreen(initialSetup, userList, userCount);
    while (devicePower)
    {
        switch (state)
        {
        case idle:
            waitForActivation(activation, state, devicePower);
            break;
        case active:
            loginUser(loginStatus, userList, loggedInUser, state, devicePower, loggedInUserName);
            chooseCommand(loginStatus, state, loggedInUserName, devicePower);
            break;
        case controlDevice:
            chooseDevice(deviceList, deviceCount, chosenDevice, state, success);
            deviceControl(deviceList, deviceCount, chosenDevice, success);
            break;
        case management:
            chooseManagementFunction(mode, state);
            managementMode(mode, userList, userCount, deviceList, deviceCount);
            break;
        }
    }
}
