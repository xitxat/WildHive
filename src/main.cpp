#include <Arduino.h>
#include "secrets.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>     //  WIFI
#include <Ticker.h>          //  WiFi
#include <AsyncMqttClient.h> //  MQTT
#include "DallasFunctions.h"
#include "SensorsWildHive.h"
#include "mqttNodeRed.h"

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

unsigned long previousMillis = 0; // Stores last time temperature was published
const long interval = 60000;      // Interval at which to publish sensor readings     RENAME to pubInterval

/* FUNCTIONS */

/*  MQTT  */
void connectToMqtt()
{
  Serial.println("****** Connecting to MQTT...");
  Serial.println("");
  Serial.println("");
  mqttClient.connect();
}

void onMqttConnect(bool sessionPresent)
{
  Serial.println(">>>>>>  Connected to MQTT.");
  Serial.print(">>>>>>  Session present: ");
  Serial.println(sessionPresent);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("Disconnected from MQTT.");

  if (WiFi.isConnected())
  {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttPublish(uint16_t packetId)
{
  Serial.print("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  // tree = packetId ;
}

/*  WIFI  */
void connectToWifi()
{
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(SECRET_SSID, SECRET_PASS); // mod
}

void onWifiConnect(const WiFiEventStationModeGotIP &event)
{
  Serial.println("******  Connected to Wi-Fi. ");
  Serial.println("");
  Serial.println(">>>>>>  Establishing MQTT connection");
  connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
{
  Serial.println("Disconnected from Wi-Fi.");
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  wifiReconnectTimer.once(2, connectToWifi);
}

void setupMqtt()
{
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  connectToWifi();
}

void setup(void)
{
  Serial.begin(9600); //  OneWire stable @ 9600
  while (!Serial)
    ;
  ;

  pinMode(MOIST_LED, OUTPUT);   // Moisture alarm led
  pinMode(WATER_LED, OUTPUT);   // Water alarm led
  pinMode(PIR_LED, OUTPUT);     // PIR alarm led
  pinMode(WATER_SENSOR, INPUT); // Water level sensor
  pinMode(PIR_SENSOR, INPUT);   // Motion detection sensor

  digitalWrite(PIR_LED, LOW); // turn LED OFF

  setupDallas(); //  DallasMinimal files
  setupMqtt();   //  WiFi & MQTT

  //********************
}

void loop(void)
{
  sensorRequest();   // via OneWire bus
  printDualProbes(); // Dallas Temp
  soilAlert();       //  Soil moisture
  delay(2000);
  waterAlert();
  delay(2000);
  detectMotion();
  //********************

  unsigned long currentMillis = millis(); // Publishes a new MQTT message (interval = 10 seconds)
  if (currentMillis - previousMillis >= interval)
  { // Save the last time a new reading was published

    previousMillis = currentMillis;
    // %d int, %f, %.3f float to 3 decimal places
    // ref: \\Summit\Code Snippits>Variable Symbols printf.docx

    // Soil Temperature.    Pub  MQTT message on topic nodemcu/dallas/temperature_soil
    uint16_t packetIdPub1 = mqttClient.publish(MQTT_PUB_SOIL_TEMP, 1, true, String(soilTemp).c_str());
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i ", MQTT_PUB_SOIL_TEMP, packetIdPub1);
    Serial.printf("Message: %.2f \n", soilTemp);

    // Water Temperature.   Pub MQTT message on topic nodemcu/dallas/temperature_water
    uint16_t packetIdPub2 = mqttClient.publish(MQTT_PUB_WATER_TEMP, 1, true, String(waterTemp).c_str());
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i ", MQTT_PUB_WATER_TEMP, packetIdPub2);
    Serial.printf("Message: %.2f \n", waterTemp);

    // Water Level.         Pub MQTT message on topic nodemcu/level/level_water
    uint16_t packetIdPub3 = mqttClient.publish(MQTT_PUB_WATER_LEVEL, 1, true, String(waterLevelValue).c_str());
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i ", MQTT_PUB_WATER_LEVEL, packetIdPub3);
    Serial.printf("Message: %d \n", waterLevelValue);

    // Moisture Level.      Pub MQTT message on topic nodemcu/level/level_moisture
    uint16_t packetIdPub7 = mqttClient.publish(MQTT_PUB_MOISTURE_LEVEL, 1, true, String(soilMoisturePercent).c_str());
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i ", MQTT_PUB_MOISTURE_LEVEL, packetIdPub7);
    Serial.printf("Message: %d \n", soilMoisturePercent);

    // Motion Detection.     Pub  MQTT message on topic nodemcu/motion_detect
    uint16_t packetIdPub4 = mqttClient.publish(MQTT_PUB_MOTION_DETECT, 1, true, String(pirVal).c_str());
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i ", MQTT_PUB_MOTION_DETECT, packetIdPub4);
    Serial.printf("Message: %d \n", pirVal);

  } // X millis mqtt send timer
}