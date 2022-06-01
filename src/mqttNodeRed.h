#ifndef MQTT_NODE_RED_H
#define MQTT_NODE_RED_H

//#include "secrets.h"


//#define MQTT_HOST IPAddress(127,0,0,1)
#define MQTT_HOST "test.mosquitto.org"
#define MQTT_PORT 1883

//  MQTT Topics
#define MQTT_PUB_SOIL_TEMP      "nodemcu/dallas/temperature_soil"
#define MQTT_PUB_WATER_TEMP     "nodemcu/dallas/temperature_water"
#define MQTT_PUB_WATER_LEVEL    "nodemcu/level/level_water"
#define MQTT_PUB_MOISTURE_LEVEL "nodemcu/level/level_moisture"
#define MQTT_PUB_MOTION_DETECT  "nodemcu/motion/motion_detect" 

//
// char ssid[] = SECRET_SSID;
// char pass[] = SECRET_PASS;





#endif