#include <Adafruit_SSD1306.h>
#include <splash.h>

#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <gfxfont.h>

#include <Wire.h>
#include <DS3231.h>
#include <OneWire.h>
#include <DallasTemperature.h>


bool displayingDate = false;

int pin = 0;

// OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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
    Serial.begin(9600);

    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }

    initClock();

    // Start sensor library
    sensors.begin();
}

// the loop function runs over and over again forever
void loop()
{
    updateDisplay();
    setLED();
    delay(100); // wait for a second
}

void updateDisplay()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    displayDateTime();
    displayTemperature();

    display.display();
}

void displayDateTime()
{
    dt = clock.getDateTime();
    String dateString = getDateString(dt);
    String timeString = getTimeString(dt);

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print(dateString);
    display.setTextSize(2);
    display.setCursor(0, 10);
    display.print(timeString);

    Serial.println(dateString + " " + timeString);
}

void displayTemperature()
{
    sensors.requestTemperatures();

    float temperature = sensors.getTempCByIndex(0);
    String tempString = String(temperature);

    display.setTextSize(1);
    display.setCursor(0, 35);
    display.print("Temperature: ");
    display.setTextSize(2);
    display.setCursor(0, 45);
    display.print(temperature);
    display.print(" ");
    display.setTextSize(1);
    display.cp437(true);
    display.write(167);
    display.setTextSize(2);
    display.print("C");

    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(sensors.getTempCByIndex(0));
}
String getDateString(RTCDateTime dt)
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

String getTimeString(RTCDateTime dt)
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