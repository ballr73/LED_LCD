#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

int pin = 0;
// init lcd
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
const int v0 = 6;
const int con = 100;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// init clock
DS3231 clock;
RTCDateTime dt;

// the setup function runs once when you press reset or power the board
void setup()
{
    Serial.begin(9600);

    initClock();
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    analogWrite(v0, con);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
}

// the loop function runs over and over again forever
void loop()
{
    dt = clock.getDateTime();
    String dateString = getDateString(dt);

    lcd.setCursor(0, 0);
    lcd.print(dateString);
    lcd.setCursor(0, 1);
    lcd.print("Temp: 0C");

    Serial.println("Formatted date:");
    Serial.println(dateString);

    Serial.print("Raw data: ");
    Serial.print(dt.year);
    Serial.print("-");
    Serial.print(dt.month);
    Serial.print("-");
    Serial.print(dt.day);
    Serial.print(" ");
    Serial.print(dt.hour);
    Serial.print(":");
    Serial.print(dt.minute);
    Serial.print(":");
    Serial.print(dt.second);
    Serial.println("");

    setLED();

    delay(1000); // wait for a second
}

String getDateString(RTCDateTime rtcDateTime)
{
    int n = 10;

    String dayString = String(dt.day);

    if (dt.day < n)
    {
        dayString = "0" + dayString;
    }

    String monthString = String(dt.month);

    if (dt.month < n)
    {
        monthString = "0" + monthString;
    }

    String yearString = String(dt.year);
    String dateString = dayString + "/" + monthString + "/" + yearString;
    return dateString;
}
void initClock()
{
    Serial.println("Init RTC module");

    clock.begin();

    // Manual (YYYY, MM, DD, HH, II, SS
    // clock.setDateTime(2016, 12, 9, 11, 46, 00);

    // Send sketch compiling time to Arduino
    clock.setDateTime(__DATE__, __TIME__);
}

void setLED()
{
    if (pin == 0)
    {
        pin = 1;
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
        pin = 0;
        digitalWrite(LED_BUILTIN, LOW);
    }
}