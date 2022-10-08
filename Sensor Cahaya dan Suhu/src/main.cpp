#include <Arduino.h>
#include <SimpleDHT.h>

#define pinDHT 7
#define sensorLDR A0
#define RED_LED D1
#define BLUE_LED D2

int nilaiSensor;
byte temperature = 0;
byte humidity = 0;

SimpleDHT11 dht11(D7);

void SensorCahayaDanSuhu()
{
  int err = SimpleDHTErrSuccess;
  nilaiSensor = analogRead(sensorLDR);

  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Pembacaan DHT11 gagal, err=");
    Serial.println(err);
    delay(1000);
    return;
  }

  Serial.print("Suhu: ");
  Serial.print((int)temperature);
  Serial.println(" *C, ");

  Serial.print("Kelembaban: ");
  Serial.print((int)humidity);
  Serial.println(" H");

  Serial.print("Cahaya: ");
  Serial.println(nilaiSensor);

  Serial.println("---------------------------");

  delay(1000);
}

void setup() {
    Serial.begin(9600);
    Serial.println("Sensor Cahaya dan Suhu");
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    delay(1000);
}

void loop() {
  SensorCahayaDanSuhu();

  if (temperature <= 27 && nilaiSensor > 900)
  {
    digitalWrite(BLUE_LED, HIGH);
    delay(250);
    digitalWrite(BLUE_LED, LOW);
    delay(250);
  }
  else if (temperature > 27 && nilaiSensor < 400 )
  {
    digitalWrite(RED_LED, HIGH);
    delay(250);
    digitalWrite(RED_LED, LOW);
    delay(250);

  }
  else
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }
}
