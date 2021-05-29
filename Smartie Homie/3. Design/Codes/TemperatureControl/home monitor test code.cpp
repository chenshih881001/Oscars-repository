#include <tempControlTest.h>
#define testFailed 0	//Define testFailed as 0
#define testPassed 1	//Define testPassed as 1

//error code:01 window malfunctioning
//error code:02 cooling system malfunctioning
//error code:03 heating system malfunctioning
//error code:04 temperature control tripped when it doesn't have to
//error code:05 temperature control not activated
//error code:06 user is not contacted
//error code:07 does not go back to monitor state

int tempControlTest(int temperatureControlState, int DesiredTemp, int InterTemp, int ExterTemp, int heating, int cooling, int windowOpen, int contactUser, int monitorState)
{
    int testResult = testPassed;

    for(int i = 0; i < 1000; i++) // Run the test 1000 times automatically
    {
        DesiredTem = rand(); // Randomise the values of the Desired temperature
        InterTem = rand(); // Randomise the values of the internal temperature
        ExterTem = rand(); // Radomise the values of external Temp

        if(DesiredTem==InterTem)															// Test of what happen if desired Temp is equal to the internal Temp
        {
            if(temperatureControlState==0) 										// if not in temperatureControlState
                else
                {
                    cout << "error code:04" << endl;
                    testResult = testFailed;												// Test failed
                }
        }

        if(DesiredTem!=InterTem) 															//Test of what happen if desired Temp is not equal to the internal Temp
        {
            if(temperatureControlState==1)										// if in temperatureControlState
                else
                {
                    cout << "error code:05" << endl;
                    testResult = testFailed;												// Test failed
                }
        }

        if(DesiredTem>InterTem) // Test of when Desired temp is higher than Intern Temp
        {
            if(ExterTem > InterTem && ExterTem > DesiredTem)     // If external Temp is bigger than both internal Temp and desired Temp
            {
                if(windowOpen = 1 && cooling == 0 && heating == 0)   //If window is open, cooling & heating are off
                    else
                    {
                        if(windowOpen == 0)															// If window is closed
                            cout << "error code:01" << endl;
                        if(cooling == 1)																// if coolin is on
                            cout << "error code:02" << endl;
                        if(heating == 1)																// if heating is on
                            cout << "error code:03" << endl;
                        testResult = testFailed;												// Test failed
                    }
            }
            else 																										//  if external Temp is smaller than internal Temp or external Temp is bigger than internal temp but smaller than desired Temp
            {
                if(windowOpen == 0; cooling == 0; heating == 1)			// if window is closed, cooling is off, heating is on
                    else
                    {
                        if(windowOpen == 1)															//if window is open
                            cout << "error code:01" << endl;
                        if(cooling == 1)																//if cooling is on
                            cout << "error code:02" << endl;
                        if(heating == 0)																//if heating is off
                            cout << "error code:03" << endl;
                        testResult = testFailed;												// Test failed
                    }
            }
        }

        else //Test of when Desired temp is lower than Intern Temp
        {
            if(InterTem > ExterTem && ExterTem < DesiredTem)				// Test of when Internal temp is higher than External Temp and External Temp is smaller than Desired Temp
            {
                if(windowOpen = 1 && cooling == 0 && heating == 0)			// If window is open, cooling off, heating off
                    else
                    {
                        if(windowOpen == 0)																// if window is closed
                            cout << "error code:01" << endl;
                        if(cooling == 1)																	// if cooling is on
                            cout << "error code:02" << endl;
                        if(heating == 1)																	// if heating is on
                            cout << "error code:03" << endl;
                        testResult = testFailed;													// Test failed
                    }
            }
            else																										// Test of when External Temp is higher than internalTemp
            {
                if(windowOpen == 0 && cooling == 1 && heating == 0)		// If window is closed, cooling is on, heating off
                    else
                    {
                        if(windowOpen == 1)															//if window is open
                            cout << "error code:01" << endl;
                        if(cooling == 0)																//if cooling is off
                            cout << "error code:02" << endl;
                        if(heating == 1)																//if heating is on
                            cout << "error code:03" << endl;
                        testResult = testFailed;												// Test failed
                    }
            }
        }

        if(contactUser) //Testing to see if the user is contacted
            else
            {
                cout << "error code:06" << endl;
                testResult = testFailed;
            }

        if(!temperatureControlState && monitorState) //Testing to see if the state return back into monitoring after the temperature control
        {
            cout << "error code:07" << endl;
            testResult = testFailed;
        }
    }
    if (testResult == testPassed)
        cout << "Temparature control tests all passed" << endl;
    return testResult;
}
