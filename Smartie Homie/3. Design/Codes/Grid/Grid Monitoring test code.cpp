#include <iostream>
using namespace std;

#include "Grid Monitoring.h"

#define testFailed 0 //Define testFailed as 0
#define testPassed 1 //Define testPassed as 1

void checkstateTest();
void movetostateTest();
void userresponseTest();
int responseTest(int resl);

int testResult = testPassed;
char response;

int main()
{
    checkstateTest();
    movetostateTest();
    userresponseTest();

    if (testResult)
        printf("All Grid Monitoring tests have passed"); //if every test passed, program returns assenting message
    return 0;
}

void checkstateTest()
{
    for (int i = 0; i < 1000; i++) // Runs the test 1000 times automatically
    {
        checkstates();
        if (batstat == count[0])
            continue;
        else
        {
            testResult = testFailed;
            printf("Error 01: incorrect Battery status!\n");
        }
        if (panstat == count[1])
            continue;
        else
        {
            testResult = testFailed;
            printf("Error 02: incorrect Panel status!\n");
        }
        if (gridstat == count[2])
            continue;
        else
        {
            testResult = testFailed;
            printf("Error 03: incorrect Grid status!\n");
        }
        if (emerstat == count[3])
            continue;
        else
        {
            testResult = testFailed;
            printf("Error 04: incorrect Emergency status!\n");
        }
    }
}

void movetostateTest()
{
    int def[4] = {};
    for (int i = 0; i < 4; i++)
    {
        count[i] = rand() % 2;
    }
    movetostate();
    if (count[0])
    {
        if (state == BatteryT)
            return;
        else
        {
            testResult = testFailed;
            printf("Error 05: can't transition to Battery Troubleshooting state!\n");
        }
    }
    if (count[1])
    {
        if (state == PanelT)
            return;
        else
        {
            testResult = testFailed;
            printf("Error 06: can't transition to Panel Troubleshooting state!\n");
        }
    }
    if (count[2])
    {
        if (state == PowerT)
            return;
        else
        {
            testResult = testFailed;
            printf("Error 07: can't transition to Power Grid Troubleshooting state!\n");
        }
    }
    if (count[3])
    {
        if (state == EmergencyMode)
            return;
        else
        {
            testResult = testFailed;
            printf("Error 08: can't transition to Emergency Mode state!\n");
        }
    }
    if (std::equal(std::begin(count), std::end(count), std::begin(def)))
        return;
    else
    {
        testResult = testFailed;
        printf("Error 09: resolved states not marked!\n");
    }
}

void userresponseTest()
{
    int res = rand() % 2;
    if (responseTest(res) == res)
        return;
    else
    {
        testResult = testFailed;
        printf("Error 10: incorrect response!\n");
    }
}

int responseTest(int resl)
{
    if (resl)
        response = 'y';
    else
        response = 'n';
    if (response == 'y')
        return 1;
    else
        return 0;
}