#include <LiquidCrystal.h>

int position = 0;
int lastPosition = 0;
int increment = 1;
int pins[] = {3, 4, 5, 6};
int sensorPin = A0;
int sensorValue = 0;
int outputValue = 0;
int ticks = 0;
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Hello");
  Serial.begin(9600);

  for (int i = 0; i < sizeof(pins); i++)
  {
    pinMode(pins[i], OUTPUT);
  }
}

void loop()
{
  ticks++;
  sensorValue = analogRead(sensorPin);
  outputValue = map(sensorValue, 0, 1023, 0, 1000);

  lcd.setCursor(0, 1);
  lcd.print(ticks);

  Serial.print("Position: ");
  Serial.print(position);
  Serial.print("\t Increment: ");
  Serial.print(increment);
  Serial.print("\t Last Position: ");
  Serial.print(lastPosition);
  Serial.print("\t Delay: ");
  Serial.println(outputValue);

  digitalWrite(pins[lastPosition], LOW);
  digitalWrite(pins[position], HIGH);

  lastPosition = position;
  position = position + increment;

  if (position == 0 || position == 3)
  {
    increment = -increment;
  }

  delay(outputValue);
}
