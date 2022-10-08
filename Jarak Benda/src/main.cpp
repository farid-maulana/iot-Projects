#include <Arduino.h>

#define triggerPin D6
#define echoPin D5

void setup() {
  Serial.begin(115200);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
  long duration, jarak;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = duration * 0.034 / 2;
  Serial.print(jarak);
  Serial.println(" cm");
  delay(2000);
}
