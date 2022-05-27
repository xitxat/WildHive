#ifndef DALLAS_FUNCTIONS_H
#define DALLAS_FUNCTIONS_H

void setupDallas();

void printAddress(DeviceAddress deviceAddress);
void printProbe(DeviceAddress deviceAddress, char* z);
void printTemperature(DeviceAddress deviceAddress);
void printResolution(DeviceAddress deviceAddress);
void printData(DeviceAddress deviceAddress);
void sensorRequest();

void printDualProbes();


#endif

















