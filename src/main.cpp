#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DallasFunctions.h"
#include "SensorsWildHive.h"


/* FUNCTIONS */


void setup(void)
{
   Serial.begin(9600); //  9600 OneWire stable
   setupDallas();      //  DallasMinimal files

   pinMode(MOIST_LED, OUTPUT);   // Moisture alarm led
   pinMode(WATER_LED, OUTPUT);   // Water alarm led
   pinMode(PIR_LED, OUTPUT);     // PIR alarm led
   pinMode(WATER_SENSOR, INPUT); // Water level sensor
   pinMode(PIR_SENSOR, INPUT);   // Motion detection sensor

   digitalWrite(PIR_LED, LOW); // turn LED OFF
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


}