#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

int pin = 0;
// LCD
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
const int v0 = 6;
const int con = 100; // LCD contrast
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// RTC
DS3231 clock;
RTCDateTime dt;

// TEMP
const int ONE_WIRE_BUS = 2;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// the setup function runs once when you press reset or power the board
void setup()
{
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);

    initClock();

    // LCD contrast
    analogWrite(v0, con);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    // Start sensor library
    sensors.begin();
}

// the loop function runs over and over again forever
void loop()
{
    displayDateTime();
    setLED();

    delay(1000); // wait for a second
}

void displayDateTime()
{
    dt = clock.getDateTime();
    String dateString = getDateString(dt);
    String timeString = getTimeString(dt);
    lcd.setCursor(0, 0);
    lcd.print(dateString + " " + timeString);
    lcd.setCursor(0, 1);
    lcd.print("Temp: 0C");
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

String getTimeString(RTCDateTime rtcDateTime)
{
    int n = 10;

    String hourString = String(dt.hour);

    if (dt.hour < n)
    {
        hourString = "0" + hourString;
    }

    String minuteString = String(dt.minute);

    if (dt.minute < n)
    {
        minuteString = "0" + minuteString;
    }

    String secondString = String(dt.second);

    if (dt.second < n)
    {
        secondString = "0" + secondString;
    }

    String timeString = hourString + ":" + minuteString + ":" + secondString;
    return timeString;
}

void initClock()
{
    Serial.println("Init RTC module");

    clock.begin();
    RTCDateTime dateTime = clock.getDateTime();

    if (dateTime.year == 2000)
    {
        // Manual (YYYY, MM, DD, HH, II, SS
        // clock.setDateTime(2016, 12, 9, 11, 46, 00);

        // Send sketch compiling time to Arduino
        clock.setDateTime(__DATE__, __TIME__);
    }
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