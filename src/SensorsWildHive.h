#ifndef SENSORS_WILD_HIVE_H
#define SENSORS_WILD_HIVE_H

#define WATER_SENSOR D5
#define MOIST_LED    D2
#define WATER_LED    D6


        /*     FCN protos   */
void moistureCap();             //  Soil moisture   
void ledFlipState(int pin);
void ledFlip(int pin);
void waterAlert();              //  Water Level
#endif