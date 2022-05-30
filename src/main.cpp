#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DallasFunctions.h"
#include "SensorsWildHive.h"

/*macro definition of water sensor and the buzzer*/
#define WATER_SENSOR D5
#define BUZZER       D6

        /* FUNCTIONS */


void pins_init() {
    pinMode(WATER_SENSOR, INPUT);
    pinMode(BUZZER, OUTPUT);
}
/************************************************************************/
/*Function: When the sensor is exposed to the water, the buzzer sounds	*/
/*			for 2 seonds.												*/
void soundAlarm() {
    for (uint8_t i = 0; i < 20; i ++) {
        digitalWrite(BUZZER, HIGH);
        delay(50);
        digitalWrite(BUZZER, LOW);
        delay(50);
    }
}
/************************************************************************/
/*Function: Determine whether the sensor is exposed to the water		*/
/*Parameter:-void           											*/
/*Return:	-boolean,if it is exposed to the water,it will return ture. */
boolean isExposedToWater() {
    if (digitalRead(WATER_SENSOR) == LOW) {
        return true;
    } else {
        return false;
    }
}

void miliBlink()
{
  
}



void setup(void)
{
  Serial.begin(9600);             //  9600 OneWire stable
  setupDallas();                  //  DallasMinimal files

    pinMode(MOIST_LED, OUTPUT);   // Moisture alarm led


    pins_init();                    //  water level

}


void loop(void)
{
sensorRequest();                  // via OneWire bus 
printDualProbes();                // Dallas Temp
moistureCap();                    //  Soil moisture









//  water level **********
    if (isExposedToWater()) {
        soundAlarm();
    }

  delay(5500);
}