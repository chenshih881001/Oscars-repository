#define ledPin 3
#define sensorPin 12
#define off 0
#define monitoring 1
#define hallwayLighting 2

int state = off;
int height = 0;
int noHumanMessage;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void turnoffLight()
{
  digitalWrite(ledPin, LOW);
  state = monitoring;
}

void turnonHallwayLight()
{
  digitalWrite(ledPin, HIGH);
  delay(6000);
  height = 0;
  state = monitoring;
}

void lookForMovement()
{
  if (digitalRead(sensorPin) == HIGH)
  {
    noHumanMessage = 0;
    Serial.println("Enter object's height: "); //Require input because no camera
  	while (Serial.available() == 0) {
    // Wait for User to Input Data
  	}
  	height = Serial.parseInt(); //Read the height
  }
  else
  {
    state = off;
  }
}

void cameraHumanCheck()
{  
    if(100<height&&height<250)  																	
    {
      Serial.println("Human detected");  
      state = hallwayLighting;
    }
  	else
    {
      if(!noHumanMessage){
      	Serial.println("No human detected");
      	noHumanMessage = 1;
      }
    }
}

void loop()
{
  switch (state)
    {
    case off:
        turnoffLight();
        break;

    case monitoring:
        lookForMovement();
    	cameraHumanCheck();
        break;

    case hallwayLighting:
        turnonHallwayLight();
        break;
    }
}

