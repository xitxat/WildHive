#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "DallasFunctions.h"

#define ONE_WIRE_BUS D3 // Data wire is plugged into D3 on the NodeMCU
#define TEMPERATURE_PRECISION 9

OneWire oneWire(ONE_WIRE_BUS);       //  communicate with any OneWire device
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.

DeviceAddress waterProbe = {0x28, 0x1C, 0x0F, 0x95, 0xF0, 0x01, 0x3C, 0x63};
DeviceAddress soilProbe = {0x28, 0x3B, 0x6B, 0x95, 0xF0, 0xFF, 0x3C, 0x1B};

    float soilTemp  = 0.0;
    float waterTemp = 0.0;


void printAddress(DeviceAddress deviceAddress) // function to print a device address
{
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print("0x");
    // zero pad the address if necessary

    if (deviceAddress[i] < 16)
      Serial.print("0"); // <16
    Serial.print(deviceAddress[i], HEX);

    if (i < 7)
    {
      Serial.print(", ");
    }
  }
}

void printProbe(DeviceAddress deviceAddress, char *z) //  includes name string
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print(z);
  Serial.print(tempC);
  Serial.println();
}

void printDualProbes()                            //  Print soil and water temps
{
  waterTemp = sensors.getTempC(waterProbe);
  Serial.print("Water temp is: ");
  Serial.println(waterTemp);
  soilTemp = sensors.getTempC(soilProbe);
  Serial.print("Soil temp is: ");
  Serial.println(soilTemp);

  Serial.println();
}

void setupDallas()
{
  sensors.begin(); // Start up the OneWire library

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
delay(200);

  // show the addresses we found on the bus
  Serial.print("Device 0 Water Probe Address: ");
  printAddress(waterProbe);
  Serial.println();
delay(200);
  Serial.print("Device 1 Soil Probe Address: ");
  printAddress(soilProbe);
  Serial.println();
delay(200);

  // set the resolution to 9 bit per device
  sensors.setResolution(waterProbe, TEMPERATURE_PRECISION);
  sensors.setResolution(soilProbe, TEMPERATURE_PRECISION);

  Serial.print("Device 0 Water Probe Resolution: ");
  Serial.println(sensors.getResolution(waterProbe), DEC);

  Serial.print("Device 1 Soil Probe Resolution: ");
  Serial.println(sensors.getResolution(soilProbe), DEC);
  Serial.println();
}

void printTemperature(DeviceAddress deviceAddress) // function to print the temperature for a device

{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
}

void printResolution(DeviceAddress deviceAddress) // function to print a device's resolution

{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();
}

void printData(DeviceAddress deviceAddress) // main function to print information about a device

{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

void sensorRequest()
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");
}
