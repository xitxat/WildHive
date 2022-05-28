#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DallasFunctions.h"



        /* FUNCTIONS */


void setup(void)
{
  Serial.begin(9600);               //  9600 OneWire stable
  setupDallas();                    //  DallasMinimal files

}


void loop(void)
{
sensorRequest();                     // via OneWire bus 
printDualProbes();                   // Dallas Temp


  delay(5500);
}