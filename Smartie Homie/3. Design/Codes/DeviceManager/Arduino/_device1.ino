#include <Wire.h>

//This is the code for the slave. This is extra so it is not as detailed

#define device1 7
#define LED 4
#define smokeDetector A0
#define masterWire 2
#define stopButton 3
#define cancel 14
#define alrmMsg 15

#define monitor 0
#define warn 1
#define Threshold 320

int state = monitor;
int resolved = 0;
int resolvedSent = 0;
int smoke;
int command;

void lookForSmoke()
{
    smoke = analogRead(smokeDetector);
    if (resolved)
        state = warn;
    else if (smoke > Threshold)
    {
        Serial.print("SMOKE!\n");
        state = warn;
    }
}

void notifyDeviceManager()
{
    digitalWrite(masterWire, HIGH);
    delay(10);
    digitalWrite(masterWire, LOW);
}

void waitAndReset()
{
    if (resolved && resolvedSent)
    {
        delay(20000);
        resolved = 0;
        resolvedSent = 0;
    }
}

void setup()
{
    Wire.begin(device1);
    Wire.onReceive(readCommand);
    Wire.onRequest(smokeWarning);
    pinMode(LED, OUTPUT);
    pinMode(smokeDetector, INPUT);
    pinMode(masterWire, OUTPUT);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(stopButton), resolution, RISING);
}

void readCommand(int command)
{
    command = Wire.read();
    if (command == 1)
    {
        Serial.print("I'm gonna turn off LED\n");
        digitalWrite(LED, LOW);
        command = 0;
    }
    else if (command == 2)
    {
        Serial.print("I'm gonna turn on LED\n");
        digitalWrite(LED, HIGH);
        command = 0;
    }
}

void smokeWarning()
{
    if (resolved)
    {
        Wire.write(cancel);
        resolvedSent = 1;
    }

    else if (smoke > Threshold)
    {
        Wire.write(alrmMsg);
    }
}

void loop()
{
    switch (state)
    {
    case monitor:
        lookForSmoke();
        waitAndReset();
        break;

    case warn:
        notifyDeviceManager();
        delay(1000);
        state = monitor;
        break;
    }
}

void resolution()
{
    resolved = 1;
}