#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define IdleState 0
#define ActiveState 1

#define Button 6
#define Phone 7
#define TV 8
#define MusicPlayer 9
#define ImmersiveLight 10


int state = IdleState;
int Input;
int Switch;
int eventMode = 0;
int immersiveMode = 0;
int Button;
String rx_byte = 0;

void printIdleMessage(){
	lcd.setCursor(0, 0);
	lcd.print("Idle State");
	delay(1000);
}

void waitForInput(){
	if (Serial.available() > 0) 
	  	rx_byte = Serial.read();
	if (rx_byte !="\0"){
		state = ActiveState;
		rx_byte = "\0";	
	}	
}

void printChooseDeviceMessage(){
	lcd.setCursor(0,0);
	lcd.print("Choose Device");
	for (int i=0; i<9, i++){
		if (Serial.available() == 0){
			lcd.setCursor(0,1);
			lcd.print("1 for Phone ");
			delay(1000);
	
			lcd.setCursor(0,1);
			lcd.print("2 for TV    ");
			delay(1000);
	
			lcd.setCursor(0,1);
			lcd.print("3 for Player");
			delay(1000);	
		}
		else 
			break;	
	}
}

void waitForChoice(){
	while (Input == 0){
		if(Serial.available() > 0)
			Input = Serial.read();
	}	
}

void printImmersiveModeMessage(){
	lcd.setCursor(0,0);
	lcd.print("Would you like");
	lcd.setCursor(0,1);
	lcd.print("immersive mode?");
	delay(2000);
}

void waitForImmersiveModeChoice(){
	while (immersiveMode == 0){
		if(Serial.available()>0)
			immersiveMode = Serial.read();
	}	
}

void executeInput(){
	if (Input == Phone)
		digitalWrite(Phone,HIGH);
	if (Input == TV)
		digitalWrite(Phone,HIGH);
	if (Input == Player)
		digitalWrite(Phone,HIGH);
	if (Input == ImmersiveLight)
		digitalWrite(ImmersiveLight,HIGH);
}


void setup(){
	pinMode(Phone, OUTPUT);
  	digitalWrite(Phone, LOW);
  	
	pinMode(TV, OUTPUT);
	digitalWrite(TV, LOW);

  	pinMode(MusicPlayer, OUTPUT);
	digitalWrite(MusicPlayer, LOW);

  	pinMode(ImmersiveLightSwitch, OUTPUT);
	digitalWrite(ImmersiveLightSwitch, LOW);

  	lcd.begin(16,2);
    pinMode(Button, INPUT);
    digitalWrite(Button, LOW);

} 	

void loop()
{
	switch(state){
	
	case IdleState:
      printIdleMessage();
      waitForInput();
      break;
      
    case ActiveState:
      printChooseDeviceMessage();
      waitForChoice();
	  printImmersiveModeMessage();
      waitForImmersiveModeChoice();
      executeInput();
	   
	}
}

