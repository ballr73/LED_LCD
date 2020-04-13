// define pins
#define PIN3 3

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN3, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(PIN3, HIGH); 
  delay(1000);
  digitalWrite(PIN3, LOW); 
  delay(1000);
  Serial.println("processing...");
}
