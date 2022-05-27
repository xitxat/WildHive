#include <Arduino.h>
//#include "defines.h"
#include <OneWire.h>
#include <DallasTemperature.h>



#define ONE_WIRE_BUS D3                   // Data wire is plugged into D3 on the NodeMCU
#define TEMPERATURE_PRECISION 9

OneWire oneWire(ONE_WIRE_BUS);            //  communicate with any OneWire device
DallasTemperature sensors(&oneWire);      // Pass our oneWire reference to Dallas Temperature.
//   DeviceAddress insideThermometer, outsideThermometer; // arrays to hold device addresses

 DeviceAddress insideThermometer    = { 0x28, 0x1C, 0x0F, 0x95, 0xF0, 0x01, 0x3C, 0x63 };
 DeviceAddress outsideThermometer   = { 0x28, 0x3B, 0x6B, 0x95, 0xF0, 0xFF, 0x3C, 0x1B };




        /* FUNCTIONS */
        // function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++){
      Serial.print("0x");
    // zero pad the address if necessary
    
    if (deviceAddress[i] < 16 ) Serial.print("0"); // <16  
    Serial.print(deviceAddress[i], HEX);

      if (i < 7) {
        Serial.print(", ");
      }
  }
}

void printProbe(DeviceAddress deviceAddress, char* z)   //  includes name string
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print(z);
  Serial.print(tempC);
  Serial.println();
}


void setup(void)
{
  Serial.begin(9600);               //  9600 OneWire stable
  delay (500);
  Serial.print("Serial.print setup");
  Serial.println("******************Serial.print printer is ON*****************");

  sensors.begin();                  // Start up the OneWire library

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");


  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  Serial.print("Device 1 Address: ");
  printAddress(outsideThermometer);
  Serial.println();

  // set the resolution to 9 bit per device
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC);
  Serial.println();

  Serial.print("Device 1 Resolution: ");
  Serial.print(sensors.getResolution(outsideThermometer), DEC);
  Serial.println();
}



// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

/*
   Main function, calls the temperatures in a loop.
*/
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

    Serial.println("******************Serial.print LOOP ON*****************");


  // print the device information
  printData(insideThermometer);
  printData(outsideThermometer);
      Serial.println("***");
  Serial.println("probe data");
    Serial.println("");

  printProbe(insideThermometer, "Water Probe Temp: ");

  delay(5500);
}