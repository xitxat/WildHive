#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DallasFunctions.h"



        /* FUNCTIONS */


void setup(void)
{
  Serial.begin(9600);               //  9600 OneWire stable

  setupDallas();

}


void loop(void)
{

sensorRequest();



  // print the device information
  // printData(waterProbe);
  // printData(soilProbe);
  //     Serial.println("***");
  // Serial.println("probe data");
  //   Serial.println("");

 // printProbe(waterProbe, "Water Probe Temp: ");
printDualProbes();
  delay(5500);
}