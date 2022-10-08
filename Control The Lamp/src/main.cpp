#include "CTBot.h"
CTBot myBot;
#define RED_LED D2
#define GREEN_LED D3
#define BLUE_LED D4

String ssid = "KOST SURYA 3";                                    // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "12345679";                                        // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "5423542524:AAF9e-ghymK1lLOaGcvUaA4nRkeZuML-eeI"; // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN

void setup()
{
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");
}

void loop()
{
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (CTBotMessageText == myBot.getNewMessage(msg))
  {
    // ...forward it to the sender
    myBot.sendMessage(msg.sender.id, msg.text);

    if (msg.text.equalsIgnoreCase("/turn_on_red"))
    {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      myBot.sendMessage(msg.sender.id, "Lampu Merah Menyala");
    }
    else if (msg.text.equalsIgnoreCase("/turn_on_green"))
    {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, LOW);
      myBot.sendMessage(msg.sender.id, "Lampu Hijau Menyala");
    }
    else if (msg.text.equalsIgnoreCase("/turn_on_blue"))
    {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, HIGH);
      myBot.sendMessage(msg.sender.id, "Lampu Biru Menyala");
    }
    else if (msg.text.equalsIgnoreCase("/turn_off"))
    {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      myBot.sendMessage(msg.sender.id, "Lampu Mati");
    }
    else
    {
      String balas;
      balas = "Maaf, perintahnya salah.";
      myBot.sendMessage(msg.sender.id, balas);
    }
  }

  // wait 500 milliseconds
  delay(500);
}