#include <Arduino.h>
#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define pinDHT 7
#define RED_LED D3
#define GREEN_LED D4
#define BLUE_LED D6

byte temperature = 0;

SimpleDHT11 dht11(D7);

void SuhuSaatIni()
{
  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read(&temperature, NULL, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Pembacaan DHT11 gagal, err=");
    Serial.println(err);
    delay(1000);
    return;
  }

  if (temperature <= 26) // Suhu Dingin
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
  }
  else if (temperature > 26 && temperature < 28) // Suhu Normal
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
  }
  else // Suhu Panas
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }
  delay(1000);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  delay(1000);

  lcd.print((int)temperature);
}

void setup()
{
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.clear();
  lcd.home();
}

void loop()
{
  lcd.home();
  SuhuSaatIni();
}
