#include <Arduino.h>
#include <SimpleDHT.h>

#define pinDHT 7     // SD3 pin signal sensor DHT
#define RED_LED D1   // led warna merah
#define GREEN_LED D2 // led warna hijau
#define BLUE_LED D3  // led warnah biru

byte temperature = 0;
byte humidity = 0;

SimpleDHT11 dht11(D7); // instan sensor dht11

void KelembabanSuhu()
{
  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Pembacaan DHT11 gagal, err=");
    Serial.println(err);
    delay(1000);
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)temperature);
  Serial.print(" *C, ");

  Serial.print((int)(4 * temperature / 5));
  Serial.print(" *R, ");

  Serial.print((int)(temperature + 273));
  Serial.print(" *K, ");

  Serial.print((int)humidity);
  Serial.println(" H");

  delay(1500);

  if (temperature <= 26)
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
  }
  else if (temperature > 26 && temperature <= 28 )
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
  }
  else
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Simple DHT");
  pinMode(RED_LED, OUTPUT); // atur pin-pin digital sebagai output
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  delay(1000);
}

void loop()
{
  KelembabanSuhu();
}
