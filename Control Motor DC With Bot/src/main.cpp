#include "CTBot.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

CTBot myBot;
int ENB = D7;
int IN3 = D1;
int IN4 = D2;

// Home
// String ssid = "TP-Link_60B2";                                    // REPLACE mySSID WITH YOUR WIFI SSID
// String pass = "farlan.frd";                                        // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
// Kost
String ssid = "KOST SURYA 3";                                    // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "12345679";                                        // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "5552575814:AAE_YajEBsFMPKWI7uYS5pZnYazuqdIvRdY"; // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN

const char *mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
String macAddr = "";

void setup_wifi()
{
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());

  macAddr = WiFi.macAddress();
  Serial.println(macAddr);
}

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (strcmp(topic, "tubes/control/curtain") == 0)
  {
    Serial.print("Changing Curtain");
    if (messageTemp == "/open")
    {
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(4000);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      Serial.println("Gorden Terbuka");
      client.publish("tubes/control/curtain", "open");
    }
    else if (messageTemp == "off")
    {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(4000);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      Serial.println("Gorden Terbuka");
      client.publish("tubes/control/curtain", "close");
    }
  }
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(macAddr.c_str()))
    {
      Serial.println("connected");
      client.subscribe("tubes/control/curtain");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  setup_wifi();
  client.setServer(mqtt_server, 1883);

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
  if (!client.connected())
  {
    reconnect();
  }

  if (!client.loop())
    client.connect(macAddr.c_str());

  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (CTBotMessageText == myBot.getNewMessage(msg))
  {
    // ...forward it to the sender
    myBot.sendMessage(msg.sender.id, msg.text);
    
    analogWrite(ENB, 767);

    if (msg.text.equalsIgnoreCase("/open"))
    {

      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(4000);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      myBot.sendMessage(msg.sender.id, "Gorden Terbuka");
      Serial.println("Gorden Terbuka");
      client.publish("tubes/control/curtain", "open");
    }
    else if (msg.text.equalsIgnoreCase("/close"))
    {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(4000);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      myBot.sendMessage(msg.sender.id, "Gorden Tertutup");
      Serial.println("Gorden Tertutup");
      client.publish("tubes/control/curtain", "close");
    }
    else
    {
      String balas;
      balas = "Maaf, perintahnya salah.";
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      myBot.sendMessage(msg.sender.id, balas);
      Serial.println("Maaf, perintahnya salah.");

    }
  }
}