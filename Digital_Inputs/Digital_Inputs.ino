#define PIN3 3
#define PIN7 7
#define PIN13 13

int P3 = 0;
int P13 = 0;
void setup()
{
    Serial.begin(9600);

    pinMode(PIN3, INPUT);
    pinMode(PIN7, OUTPUT);
    pinMode(PIN13, OUTPUT);
}

void loop()
{
    P3 = digitalRead(PIN3);

    digitalWrite(13, LOW);

    Serial.println(P3);

    if (P3 == 1)
    {
        digitalWrite(PIN7, HIGH);
    }
    else
    {
        digitalWrite(PIN7, LOW);
    }

    delay(1000);
    digitalWrite(PIN13, HIGH);
}