#include <Wire.h>

//This is the code for the slave. This is extra so it is not as detailed

#define device2 9
#define LED 10
#define Alarm 7

int command;
int alarm = 0;

void setup()
{
    Wire.begin(device2);
    Wire.onReceive(readCommand);
    pinMode(LED, OUTPUT);
    pinMode(Alarm, OUTPUT);
    Serial.begin(9600);
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
    else if (command == 3)
    {
        if (!alarm)
        {
            Serial.print("I'm gonna turning on the alarm\n");
            tone(Alarm, 700);
            command = 0;
            alarm = 1;
        }
    }
    else if (command == 4)
    {
        if (alarm)
        {
            Serial.print("I'm gonna turning off the alarm\n");
            noTone(Alarm);
            command = 0;
            alarm = 0;
        }
    }
}

void loop()
{
}