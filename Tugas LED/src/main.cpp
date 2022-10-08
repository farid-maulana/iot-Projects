#include <Arduino.h>

#define GREEN_LED D6

void setup() {
  Serial.begin(115200);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(2, OUTPUT);

  Serial.println("Contoh Program LED SOS");
}

void loop() {

  // 3 dits (3 titik atau huruf S)
  for (int x = 0; x < 3; x++)
  {
    digitalWrite(GREEN_LED, HIGH);  // LED nyala
    delay(150);                     // delay selama 150ms
    digitalWrite(GREEN_LED, LOW);   // LED mati
    delay(100);                     // delay selama 100ms
  }
  digitalWrite(GREEN_LED, HIGH);

  // 100ms delay to cause slight gap between letters
  delay(500);

  // 3 dash (3 garis atau huruf O)
  for (int x = 0; x < 3; x++)
  {
    digitalWrite(2, HIGH);  // LED nyala
    delay(400);             // delay selama 400ms
    digitalWrite(2, LOW);   // LED mati
    delay(100);             // delay selama 100ms
  }

  // 100ms delay to cause slight gap between letters
  delay(500);

  // 3 dits again (3 titik atau huruf S)
  for (int x = 0; x < 3; x++)
  {
    digitalWrite(D0, HIGH); // LED nyala
    delay(150);             // delay selama 150ms
    digitalWrite(D0, LOW);  // LED mati
    delay(100);             // delay selama 100ms
  }

  // wait 5 seconds before repeating the SOS signal
  delay(500);
}
