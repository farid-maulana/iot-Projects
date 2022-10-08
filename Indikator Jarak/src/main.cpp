#include <Arduino.h>

#define RED_LED D1
#define GREEN_LED D2
#define BLUE_LED D3
#define triggerPin D6
#define echoPin D5

void setup()
{
  Serial.begin(115200);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  delay(3000);
}

void loop()
{
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

  if (jarak == 1)
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
  }
  else if (jarak == 2)
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
  }
  else if (jarak == 3)
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }
  else
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    delay(1000);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    delay(1000);
  }
  delay(1000);
}
