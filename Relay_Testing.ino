#include <Wire.h>
#include <ACS712.h>

#define ACS712_PIN A0
#define RELAY_PIN D7

ACS712 acs712(ACS712_05B, ACS712_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  float current = acs712.getCurrentDC();
  Serial.print("Current: ");
  Serial.print(current, 2);
  Serial.println("A");

  if (current > 0.90) {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Relay off");
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Relay on");
  }

  delay(1000);
}
