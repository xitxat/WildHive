#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DallasMinimal.h"



        /* FUNCTIONS */


void setup(void)
{
  Serial.begin(9600);               //  9600 OneWire stable

  setupDallas();

}


void loop(void)
{

sensorRequest();



printDualProbes();
  delay(5500);
}