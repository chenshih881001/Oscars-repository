// include the library code:
#include <LiquidCrystal.h>
#define INC 0
#define USE 1
#define MinUsage 200

int blevel(int bat);
void printlevel(int lvl);
int charging(int bat);

int const NoPow = 0;
int const Charge = 1;
int const Share = 2;
int const Discharge = 3;

int inc;
int use;
int state;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//set battery icon
byte BatteryLCD1[8] = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F};
byte BatteryLCD2[8] = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x1F};
byte BatteryLCD3[8] = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x1F};
byte BatteryLCD4[8] = {0x0E, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F};
byte BatteryLCD5[8] = {0x0E, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
byte BatteryLCD6[8] = {0x0E, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
byte BatteryLCD7[8] = {0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};

int battery = rand() % 101;

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Op:");
  lcd.createChar(1, BatteryLCD1);
  lcd.createChar(2, BatteryLCD2);
  lcd.createChar(3, BatteryLCD3);
  lcd.createChar(4, BatteryLCD4);
  lcd.createChar(5, BatteryLCD5);
  lcd.createChar(6, BatteryLCD6);
  lcd.createChar(7, BatteryLCD7);
  lcd.setCursor(15, 0);
  lcd.write(1);
}

int charging(int bat)
{
  lcd.setCursor(0, 1);
  lcd.write("Charging        ");
  while (bat < 105)
  {
    printlevel(bat);
    delay(10);
    bat++;
  }
  return bat;
}

int decharging(int bat)
{
  lcd.setCursor(0, 1);
  lcd.write("Discharging   ");
  while (bat > 0)
  {
    printlevel(bat);
    delay(20);
    bat--;
  }
  return bat;
}

int blevel(int bat)
{
  if (bat >= 100)
    return 7;
  else if (bat >= 80)
    return 6;
  else if (bat >= 60)
    return 5;
  else if (bat >= 40)
    return 4;
  else if (bat >= 20)
    return 3;
  else if (bat >= 0)
    return 2;
  else
    return 1;
}

void printlevel(int lvl)
{
  lcd.setCursor(15, 0);
  lcd.write(blevel(lvl));
}

void loop()
{
  printlevel(battery);
  inc = analogRead(INC);
  use = analogRead(USE);

  switch (state)
  {
  case NoPow: //Power House State
    lcd.setCursor(0, 1);
    lcd.write("No Power        ");
    if (inc > use)
    {
      if (battery >= 100)
      {
        state = Share;
      }
      else
      {
        state = Charge;
      }
    }
    break;

  case Charge: //Charge Battery State
    battery = charging(battery);
    lcd.setCursor(0, 1);
    lcd.write("Battery Full    ");
    delay(500);

    if (inc > use)
    {
      state = Share;
    }
    else if (inc <= use)
    {
      state = Discharge;
    }
    break;
  case Share: //Return to Grid State
    lcd.setCursor(0, 1);
    lcd.write("Sharing         ");
    if (inc <= use)
    {
      state = Discharge;
    }
    break;
  case Discharge: //Power House State
    battery = decharging(battery);
    if (inc > use)
      state = Charge;
    if (inc <= use)
      state = NoPow;
    break;
  }
}
