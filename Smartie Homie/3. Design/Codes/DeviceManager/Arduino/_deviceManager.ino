#include <Wire.h>

#define idle 0 //Define states
#define active 1

#define RED 8 //Define colour pins
#define BLUE 6
#define GREEN 5 // RED = off; BLUE = transmitting; GREEN = on

#define device1 7 //Device address define
#define device2 9

#define device1Emergency 3
#define SmkAlrm 3
#define SmkAlrmOff 4

#define OFF 1 //Define switch
#define ON 2

/* This code is only to simulate the management of the devices. 
The tool is too limited to work with remote activation, voice control, etc.
I2C is used to simulate remote communication of multiple devices to the device manager via Bluetooth.*/

int state = idle;
int commandReceived;
int chooseDevice;
int turnOn;
int turnOff;
int return2Idle;
int deviceCommand;
int deviceCall;
int smokeAlarm;
int smokeResolved;

String idleMessage = "I'm idling.\n";
String activeMessage = "How may I help you?\n";
String activateMessage = "wake up stella";
String turnOn1 = "turn on 1";
String turnOn2 = "turn on 2";
String turnOff1 = "turn off 1";
String turnOff2 = "turn off 2";
String invalidCommand = "Sorry, invalid command received.\n";
String commandReceiveMessage = "Command received.\n";
String commandSent = "Command sent\n";
String smkResolved = "14";
String smokeWarning = "15";
String receiveBuffer;

void turnOnIdleLight()
{
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  delay(100);
}

void turnOnActiveLight()
{
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
  delay(100);
}

void printIdleMessage()
{
  Serial.print(idleMessage);
  delay(100);
}

void printActiveMessage()
{
  if (!deviceCommand)
  {
    Serial.print(activeMessage);
    delay(100);
  }
}

void waitForActivation()
{
  while (state == idle)
  {
    if (Serial.available() > 0)
    {
      receiveBuffer = Serial.readString();
      if (receiveBuffer == activateMessage)
      {
        state = active;
        delay(100);
      }
    }
    else if (deviceCall)
    {
      Wire.requestFrom(device1, 1);
      receiveBuffer = Wire.read();
      state = active;
      commandReceived = 1;
      deviceCommand = 1;
      delay(100);
    }
  }
}

void waitForCommand()
{
  if (!deviceCommand)
  {
    chooseDevice = 0;
    turnOn = 0;
    turnOff = 0;
    for (int i = 0; i < 500; i++)
    {
      if (Serial.available() > 0)
      {
        receiveBuffer = Serial.readString();
        commandReceived = 1;
        Serial.print(commandReceiveMessage);
        delay(100);
        break;
      }
      else
      {
        delay(10);
      }
    }
  }
  else if (deviceCommand || deviceCall)
  {
    if (deviceCall && !commandReceived)
    {
      Wire.requestFrom(device1, 1);
      receiveBuffer = Wire.read();
      state = active;
      commandReceived = 1;
      deviceCommand = 1;
      delay(100);
    }
  }

  if (!commandReceived)
  {
    deviceCommand = 0;
    return2Idle = 1;
  }
}

void analyseCommand()
{
  if (commandReceived)
  {
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
    delay(500);
    if (receiveBuffer == turnOn1)
    {
      chooseDevice = device1;
      turnOn = 1;
      delay(100);
    }
    else if (receiveBuffer == turnOn2)
    {
      chooseDevice = device2;
      turnOn = 1;
      delay(100);
    }
    else if (receiveBuffer == turnOff1)
    {
      chooseDevice = device1;
      turnOff = 1;
      delay(100);
    }
    else if (receiveBuffer == turnOff2)
    {
      chooseDevice = device2;
      turnOff = 1;
      delay(100);
    }
    else if (receiveBuffer == smokeWarning)
    {
      smokeAlarm = 1;
      smokeResolved = 0;
      delay(100);
    }

    else if (receiveBuffer == smkResolved)
    {
      smokeAlarm = 0;
      smokeResolved = 1;
      delay(100);
    }

    else
    {
      Serial.print(invalidCommand);
      commandReceived = 0;
      delay(100);
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, HIGH);
    }
  }
}

void executeCommand()
{
  if (commandReceived)
  {
    if (turnOn)
    {
      Wire.beginTransmission(chooseDevice);
      Wire.write(ON);
      Wire.endTransmission();
      Serial.print(commandSent);
      delay(100);
    }
    if (turnOff)
    {
      Wire.beginTransmission(chooseDevice);
      Wire.write(OFF);
      Wire.endTransmission();
      Serial.print(commandSent);
      delay(100);
    }
    if (smokeAlarm)
    {
      Wire.beginTransmission(device2);
      Wire.write(SmkAlrm);
      Wire.endTransmission();
      Serial.print("SMOKE! SMOKE! SMOKE!\n");
      deviceCall = 0;
      delay(100);
    }
    if (smokeResolved)
    {
      Wire.beginTransmission(device2);
      Wire.write(SmkAlrmOff);
      Wire.endTransmission();
      Serial.print("Smoke alarm is off.\n");
      deviceCall = 0;
      delay(100);
    }
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, HIGH);
    delay(100);
  }
  commandReceived = 0;
}

void returnToIdle()
{
  if (return2Idle)
  {
    return2Idle = 0;
    state = idle;
    delay(100);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Wire.begin();
  attachInterrupt(digitalPinToInterrupt(device1Emergency), openCommDevice1, RISING);
}

void loop()
{
  switch (state)
  {
  case idle:
    turnOnIdleLight();
    printIdleMessage();
    waitForActivation();
    break;

  case active:
    turnOnActiveLight();
    printActiveMessage();
    waitForCommand();
    analyseCommand();
    executeCommand();
    returnToIdle();
    break;
  }
}

void openCommDevice1()
{
  deviceCall = 1;
}