#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DallasFunctions.h"
#include "SensorsWildHive.h"

/*macro definition of water sensor and the buzzer*/


        /* FUNCTIONS */


void pins_init() {
    pinMode(WATER_SENSOR, INPUT);

}



void setup(void){
  Serial.begin(9600);             //  9600 OneWire stable
  setupDallas();                  //  DallasMinimal files

    pinMode(MOIST_LED, OUTPUT);   // Moisture alarm led
    pinMode(WATER_LED, OUTPUT);   // Water alarm led

    pins_init();                    //  water level
}

void loop(void){
sensorRequest();                  // via OneWire bus 
printDualProbes();                // Dallas Temp
moistureCap();                    //  Soil moisture
   delay(2000);
waterAlert();

   delay(2000);
}