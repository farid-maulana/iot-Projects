#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SimpleDHT.h>

const char *ssid = "TP-Link_60B2";
const char *password = "farlan.frd";
const char *mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

#define RED_LED D2
#define GREEN_LED D3
#define BLUE_LED D4
#define LDR A0

SimpleDHT11 dht11(D7);

long now = millis();
long lastMeasure = 0;
String macAddr = "";

void setup_wifi()
{
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
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

  if (strcmp(topic, "control/lamp/red") == 0)
  {
    Serial.print("Changing Room lamp to ");
    if (messageTemp == "on")
    {
      digitalWrite(RED_LED, HIGH);
      Serial.print("Red On");
    }
    else if (messageTemp == "off")
    {
      digitalWrite(RED_LED, LOW);
      Serial.print("Red Off");
    }
  }

  if (strcmp(topic, "control/lamp/green") == 0)
  {
    Serial.print("Changing Room lamp to ");
    if (messageTemp == "on")
    {
      digitalWrite(GREEN_LED, HIGH);
      Serial.print("Green On");
    }
    else if (messageTemp == "off")
    {
      digitalWrite(GREEN_LED, LOW);
      Serial.print("Green Off");
    }
  }

  if (strcmp(topic, "control/lamp/blue") == 0)
  {
    Serial.print("Changing Room lamp to ");
    if (messageTemp == "on")
    {
      digitalWrite(BLUE_LED, HIGH);
      Serial.print("Blue On");
    }
    else if (messageTemp == "off")
    {
      digitalWrite(BLUE_LED, LOW);
      Serial.print("Blue Off");
    }
  }
  Serial.println();
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(macAddr.c_str()))
    {
      Serial.println("connected");
      client.subscribe("control/lamp/red");
      client.subscribe("control/lamp/green");
      client.subscribe("control/lamp/blue");
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
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }

  if (!client.loop())
    client.connect(macAddr.c_str());

  now = millis();
  if (now - lastMeasure > 5000)
  {
    lastMeasure = now;
    int err = SimpleDHTErrSuccess;

    byte temperature = 0;
    byte humidity = 0;
    int brightness;

    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
    {
      Serial.print("Pembacaan DHT11 gagal, err=");
      Serial.println(err);
      delay(1000);
      return;
    }

    static char temperatureTemp[7];
    dtostrf(temperature, 4, 2, temperatureTemp);

    static char humidityTemp[7];
    dtostrf(humidity, 6, 2, humidityTemp);

    brightness = analogRead(LDR);
    static char brighnessVal[7];
    dtostrf(brightness, 6, 2, brighnessVal);

    client.publish("monitoring/temperature", temperatureTemp);
    client.publish("monitoring/humidity", humidityTemp);
    client.publish("cahaya", brighnessVal);

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t Temperature: ");
    Serial.print(temperature);
    Serial.print(" *C ");
    Serial.print(" %\t Brightness: ");
    Serial.print(brightness);
    Serial.print(" Lux");
    Serial.println();
  }
}
