#ifndef DALLAS_MINIMAL_H
#define DALLAS_MINIMAL_H

void setupDallas();

void printAddress(DeviceAddress deviceAddress);
void printProbe(DeviceAddress deviceAddress, char* z);
void printTemperature(DeviceAddress deviceAddress);
void printResolution(DeviceAddress deviceAddress);
void printData(DeviceAddress deviceAddress);
void sensorRequest();

void printDualProbes();


#endif
