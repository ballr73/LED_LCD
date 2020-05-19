#include "pitches.h";
#define PIN3 3
#define PIN7 7
#define BUZZER 8
#define PIN13 13

int buttonState = 0;
int P13 = 0;

int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int durations[] = {
    4, 8, 8, 4, 4, 4, 4, 4};

void setup()
{
    Serial.begin(9600);

    pinMode(PIN3, INPUT);
    pinMode(PIN7, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(PIN13, OUTPUT);
}

void loop()
{
    buttonState = digitalRead(PIN3);

    digitalWrite(13, LOW);

    Serial.println(buttonState);

    if (buttonState == 1)
    {
        digitalWrite(PIN7, HIGH);

        for (int note = 0; note < 8; note++)
        {
            int duration = 1000 / durations[note];
            tone(BUZZER, melody[note], duration);
            int pause = duration * 1.30;
            delay(pause);
            noTone(BUZZER);
        }
    }
    else
    {
        digitalWrite(PIN7, LOW);
    }

    delay(1000);
    digitalWrite(PIN13, HIGH);
}