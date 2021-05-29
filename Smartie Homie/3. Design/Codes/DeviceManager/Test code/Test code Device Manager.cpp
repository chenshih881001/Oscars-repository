#include <ctime>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <sstream>
#include "deviceManager.h"

#define testFailed 0
#define testPassed 1

using namespace std;

int testResult = testPassed;

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
std::string response;

string nameList[10] = {"Alex", "Stephanie", "Roger", "Robert", "Mia", "Lester", "Ruth", "Roman", "Violet", "Elise"};
int dayOfBirthList[10] = {23, 21, 13, 4, 13, 12, 25, 12, 12, 21};
int monthOfBirthList[10] = {3, 4, 5, 8, 7, 2, 6, 3, 12, 11};
int yearOfBirthList[10] = {2000, 1990, 1995, 1984, 1999, 2000, 1989, 1991, 2001, 1994};
char genderList[10] = {'M', 'F', 'M', 'M', 'F', 'M', 'F', 'M', 'F', 'F'};
int ageList[10] = {20, 30, 25, 36, 21, 20, 31, 29, 19, 26};

string deviceNameList[10] = {"TV", "Lamp", "Flash light", "Hair Dryer", "Coffee Maker", "Treadmill", "Pace maker", "Laptop", "Fridge", "Phone"};

void userClassTest(int &testResult, int i)
{
    userList.push_back(user());
    userList[i].userName = nameList[i]; // Assign the value of the variable the same as the list
    userList[i].gender = genderList[i];
    userList[i].dayOfBirth = dayOfBirthList[i];
    userList[i].monthOfBirth = monthOfBirthList[i];
    userList[i].yearOfBirth = yearOfBirthList[i];
    string nameTest = userList[i].returnUserName(); //Test the return username function
    if (nameTest != nameList[i])
    {
        cout << "ERR_1: Return user's name function is not working." << endl;
        testResult = testFailed;
    }
    userList[i].getCurrentDate();
    userList[i].convertDoB2Age(); //Test the age converter
    if (userList[i].userAge != ageList[i])
    {
        cout << "ERR_2: Age converter is not working." << endl;
        testResult = testFailed;
    }
}

void deviceClassTest(int &testResult, int i)
{
    device newDevice;
    newDevice.deviceName = deviceNameList[i]; // Assign it a name
    string a = newDevice.returnDeviceName();
    if (a != deviceNameList[i])
    {
        cout << "ERR_3: Return device name is faulty." << endl;
        testResult = testFailed;
    }
    int b = rand() % 2; // Randomise a variable
    newDevice.status = b;
    int c = newDevice.returnDeviceStatus(); // Test return device status function
    if (b != c)
    {
        cout << "ERR_4: Return device status is faulty." << endl;
        testResult = testFailed;
    }
    newDevice.deviceSwitch(); // Test device switch
    c = newDevice.returnDeviceStatus();
    if (b == c)
    {
        cout << "ERR_5: Device switch is faulty." << endl;
        testResult = testFailed;
    }
}

waitForActivationModuleTest(int &testResult, std::string &activation, int &state, int &devicePower)
{
    activation = "Wake up, Stella"; //Wake up test
    waitForActivation(activation, state, devicePower);
    if (activation == "Wake up, Stella" && state != active)
    {
        cout << "ERR_6: Wake up call is not working." << endl;
        testResult = testFailed;
    }
    activation = "Power Off"; //Power off test
    waitForActivation(activation, state, devicePower);
    if (activation == "Power Off" && devicePower != off)
    {
        cout << "ERR_7: Device is not shutting off in activation module." << endl;
        testResult = testFailed;
    }
    state = idle;
    devicePower = on;
    activation = "sdasdasfqwqwfqwf"; //Random input test
    waitForActivation(activation, state, devicePower);
    if (activation != "Power Off" && activation != "Wake up, Stella" && state == active)
    {
        cout << "ERR_8: Device switching to active without prompt in activation module." << endl;
        testResult = testFailed;
    }
    else if (activation != "Power Off" && activation != "Wake up, Stella" && devicePower == off)
    {
        cout << "ERR_9: Device turning off without prompt in activation module." << endl;
        testResult = testFailed;
    }
}

void loginUserTest(int &testResult, int i, int &loginStatus, std::vector<user> userList, int &loggedInUser, int &state, int &devicePower, std::string &loggedInUserName, std::string &response)
{
    loginStatus = 1;
    response = userList[i].userName;
    loggedInUser = 829104;
    loginUser(loginStatus, userList, loggedInUser, state, devicePower, loggedInUserName, response); //test login function when the device has already been logged in.
    if (loggedInUser == i || loggedInUserName == userList[i].userName)
    {
        cout << "ERR_10: Device is running the login function even though it has already been logged in." << endl;
        testResult = testFailed;
    }
    loginStatus = 0;
    response = userList[i].userName;
    loginUser(loginStatus, userList, loggedInUser, state, devicePower, loggedInUserName, response); //test login function when the device is not logged in.
    if (loggedInUser != i)
    {
        cout << "ERR_11: Device is not recognising the user's position within the list." << endl;
        testResult = testFailed;
    }
    if (loggedInUserName != userList[i].userName)
    {
        cout << "ERR_12: Device is not recognising the user's name." << endl;
        testResult = testFailed;
    }
    if (!loginStatus)
    {
        cout << "ERR_13: Device is not logging in user." << endl;
        testResult = testFailed;
    }
    response = "sadklajdklajskldjaklsjd";
    loginStatus = 0;
    loginUser(loginStatus, userList, loggedInUser, state, devicePower, loggedInUserName, response); //test login function when the user name is invalid.
    if (loginStatus)
    {
        cout << "ERR_14: Device is logging in random input." << endl;
        testResult = testFailed;
    }
    response = "Power Off";
    loginStatus = 0;
    loginUser(loginStatus, userList, loggedInUser, state, devicePower, loggedInUserName, response); //test login function power off.
    if (devicePower)
    {
        cout << "ERR_15: Device is not switching off." << endl;
        testResult = testFailed;
    }
    response = "Idle";
    loginStatus = 0;
    loginUser(loginStatus, userList, loggedInUser, state, devicePower, loggedInUserName, response); //test login function's return to idle.
    if (state != idle)
    {
        cout << "ERR_16: Device is not returning to idle." << endl;
        testResult = testFailed;
    }
}

void chooseCommandTest(int &testResult, int i, int &loginStatus, int &state, std::string loggedInUserName, int &devicePower, std::string &response)
{
    loginStatus = 0; //Test what does the function does when there are no user logged in
    response = '1';
    chooseCommand(loginStatus, state, loggedInUserName, devicePower, response);
    if (state == controlDevice)
    {
        cout << "ERR_17: Function is running even though not logged in." << endl;
        testResult = testFailed;
    }
    loginStatus = 1; //Test change to control device
    response = '1';
    chooseCommand(loginStatus, state, loggedInUserName, devicePower, response);
    if (state != controlDevice)
    {
        cout << "ERR_18: Device is not switching to control mode." << endl;
        testResult = testFailed;
    }
    loginStatus = 1; //Test change to management
    response = '2';
    chooseCommand(loginStatus, state, loggedInUserName, devicePower, response);
    if (state != management)
    {
        cout << "ERR_19: Device is not switching to management mode." << endl;
        testResult = testFailed;
    }
    loginStatus = 1; //Test change to management
    response = '3';
    chooseCommand(loginStatus, state, loggedInUserName, devicePower, response);
    if (state != idle)
    {
        cout << "ERR_20: Device is not switching to idle." << endl;
        testResult = testFailed;
    }
    loginStatus = 1; //Test power off
    response = '4';
    chooseCommand(loginStatus, state, loggedInUserName, devicePower, response);
    if (devicePower)
    {
        cout << "ERR_21: Device is not switching off." << endl;
        testResult = testFailed;
    }
    loginStatus = 1; //Test logging out
    response = '5';
    chooseCommand(loginStatus, state, loggedInUserName, devicePower, response);
    if (loginStatus)
    {
        cout << "ERR_22: Device is not loging out." << endl;
        testResult = testFailed;
    }
    loginStatus = 1; // Reset variables
    devicePower = 1;
    state = active;
    response = 'asdasfasgasgdasdkasdl;asdl;kasl;dksa'; //Test random input
    chooseCommand(loginStatus, state, loggedInUserName, devicePower, response);
    if (!loginStatus || state == idle || state == management || state == controlDevice || !devicePower)
    {
        cout << "ERR_23: Device is reacting to random input in choose mode." << endl;
        testResult = testFailed;
    }
}

void printResult(int testResult)
{
    if (testResult == testPassed)
        cout << "Test has completed successfully!" << endl;
    else
        cout << "Test FAILED, we'll get em' next time!" << endl;
}

int main()
{
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        userClassTest(testResult, i);
        deviceClassTest(testResult, i);
        waitForActivationModuleTest(testResult, activation, state, devicePower);
        loginUserTest(testResult, i, loginStatus, userList, loggedInUser, state, devicePower, loggedInUserName, response);
        chooseCommandTest(testResult, i, loginStatus, state, loggedInUserName, devicePower, response);
    }
    printResult(testResult);
    return testResult;
}
