#ifndef SENSORS_WILD_HIVE_H
#define SENSORS_WILD_HIVE_H

#define PIR_SENSOR   D1   
#define WATER_SENSOR D2         // Level

#define MOIST_LED    D5  
#define WATER_LED    D6
#define PIR_LED      D7                // the pin that the LED is atteched to

        /*     FCN protos   */
void ledFlip(int pin);          //  Blink
void soilAlert();               //  Soil moisture   
void waterAlert();              //  Water Level
void detectMotion();            //  PIR sensor

#endif