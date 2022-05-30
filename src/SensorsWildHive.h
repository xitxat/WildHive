#ifndef SENSORS_WILD_HIVE_H
#define SENSORS_WILD_HIVE_H

#define MOIST_LED    D2
#define WATER_LED    D6

        /*     FCN protos   */
void moistureCap();             //  Soil moisture



void millisBlink(int pin, unsigned long duration);
#endif