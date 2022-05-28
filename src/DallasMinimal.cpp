#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "DallasMinimal.h"

#define ONE_WIRE_BUS D3 // Data wire is plugged into D3 on the NodeMCU
#define TEMPERATURE_PRECISION 9

OneWire oneWire(ONE_WIRE_BUS);       //  communicate with any OneWire device
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.

DeviceAddress waterProbe = {0x28, 0x1C, 0x0F, 0x95, 0xF0, 0x01, 0x3C, 0x63};
DeviceAddress soilProbe = {0x28, 0x3B, 0x6B, 0x95, 0xF0, 0xFF, 0x3C, 0x1B};



void setupDallas()
{
    sensors.begin(); // Start up the OneWire library

    // // locate devices on the bus
    // Serial.print("Locating devices...");
    // Serial.print("Found ");
    // Serial.print(sensors.getDeviceCount(), DEC);
    // Serial.println(" devices.");

    // // show the addresses we found on the bus
    // Serial.print("Device 0 Water Probe Address: ");
    // printAddress(waterProbe);
    // Serial.println();

    // Serial.print("Device 1 Soil Probe Address: ");
    // printAddress(soilProbe);
    // Serial.println();

    // set the resolution to 9 bit per device
    sensors.setResolution(waterProbe, TEMPERATURE_PRECISION);
    sensors.setResolution(soilProbe, TEMPERATURE_PRECISION);

    // Serial.print("Device 0 Water Probe Resolution: ");
    // Serial.print(sensors.getResolution(waterProbe), DEC);
    // Serial.println();

    // Serial.print("Device 1 Soil Probe Resolution: ");
    // Serial.print(sensors.getResolution(soilProbe), DEC);
    // Serial.println();
}

void sensorRequest() // via OneWire bus
{
    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus
    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures();
    Serial.println("DONE");
}

// void printDualProbes()
// {
//     float waterTemp = sensors.getTempC(waterProbe);
//     Serial.print("Water temp is: ");
//     Serial.print(waterTemp);
//     Serial.println();
//     float soilTemp = sensors.getTempC(soilProbe);
//     Serial.print("Soil temp is: ");
//     Serial.print(soilTemp);
//     Serial.println();

//     Serial.println();

// }
