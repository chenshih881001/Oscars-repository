#include <stdio.h>
#include <math.h>
#define monitoring 0
#define heating 1
#define cooling 2

//Implementation of the temp control

static int state = monitoring;
static int heating;
static int cooling;
static int windowOpen;
static int contactUser;

int main(int DesiredTemp, int InterTemp, int ExterTemp)
{  	
/*
HERE IS THE DISPUTE (INPUT RANDOMISATION)
   	desiredTemp = rand();
  	externTemp = rand();
  	internTemp = rand();

*/

switch(state){
	case monitoring: 
 	 {
  	if(DesiredTemp>int InterTemp)
    	state = heating;
  	if(DeiredTemp<int InternTemp)
    	state = cooling;
  	}
  
  case heating:
  	heating(int DesiredTemp, int InterTemp, int ExterTemp, int heating, int cooling, int windowOpen);
  
  case cooling:
  	cooling(int DesiredTemp, int InterTemp, int ExterTemp, int heating, int cooling, int windowOpen);
	}
}

void heating(int DesiredTemp, int InterTemp, int ExterTemp, int heating, int cooling, int windowOpen)
{
	if (DesiredTemp == InterTemp)
  	{
    state = monitoring;
    printf("Returned to mornitoring.\n");
    }
  
  if (InterTemp>ExterTemp || InterTemp<ExterTemp && ExterTemp<DesiredTemp)
  	{
  	heating = 1;
    cooling = 0;
    window = 0;
    printf("Heating is turned on\n");
  	}
    
  if (InterTemp<ExterTemp && ExterTemp>DesiredTemp)
  	{
  	heating = 0;
    cooling = 0;
    window = 1;
    printf("Window is opened.\n");
 		}
}

void cooling(int DesiredTemp, int InterTemp, int ExterTemp, int heating, int cooling, int windowOpen)
{
	if (DesiredTemp == InterTemp)
  	{
    state = monitoring;
    printf("Returned to mornitoring\n");
    }

  if (InterTemp<ExterTemp || InterTemp>ExterTemp && ExterTemp>DesiredTemp)
  	{
  	heating = 0;
    cooling = 1;
    window = 0;
    printf("Cooling is turned on\n");
  	}

if (InterTemp>ExterTemp && ExterTemp<DesiredTemp)
  	{
  	heating = 0;
    cooling = 0;
    window = 1;
    printf("Window is opened.\n");
 		}
}



