#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;

#include "Grid Monitoring.h"

//Implementation of the grid monitoring
int main()
{
    srand(time(NULL));
    while (x == 0)
    {
        switch (state)
        {
        case Monitoring:
            monitor();
            break;

        case EmergencyMode:
            emert();
            if (isitfalse())
            {
                movetostate();
                break;
            }
            else
                state = EmergencyS;
            break;

        case BatteryT:
            batt();
            if (isitresolved())
            {
                movetostate();
                break;
            }
            else
                state = ServiceMode;
            break;
        case PanelT:
            pant();
            if (isitresolved())
            {
                movetostate();
                break;
            }
            else
                state = ServiceMode;

            break;
        case PowerT:
            powt();
            if (isitresolved())
            {
                movetostate();
                break;
            }
            else
                state = ServiceMode;
            break;

        case Panelreset:
            panelres();
            if (isitresolved())
            {
                movetostate();
                break;
            }
            else
                state = ServiceMode;
            break;

        case ServiceMode:
            printservice();
            if (isitresolved())
            {
                movetostate();
                break;
            }
            else
                printdeepserv();
            break;
        case EmergencyS:
            printemergency();
            if (isitresolved())
            {
                movetostate();
                break;
            }
            else
                printdeepem();
            break;
        }
    }
}
