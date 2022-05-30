#include <Arduino.h>

#include "SensorsWildHive.h"

/* LEDs      */
int ledState = LOW;
int blueLedState = LOW;

/* Moisture sensor calibration */
const int AirValue = 600;   // Dry  2% @580
const int WaterValue = 300; // Wet 98% @250 immersion value
int soilMoistureValue = 0;
int soilMoisturePercent = 0;

/*     BLINK    */
void ledFlip(int pin)              //  BLUE led for water
{                                  //  Yellow led for moisture                     
         digitalWrite(pin , HIGH);
         delay(200);
         digitalWrite(pin , LOW);
         delay(200);
}

/*     MOISTURE    */
void moistureCap()
{
    soilMoistureValue = analogRead(A0); // NodeMcu only 1 ADC (A0)
    Serial.print("Analog Pin reading: ");
    Serial.println(soilMoistureValue);

    soilMoisturePercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    Serial.print("Soil moisture ");
    Serial.print(soilMoisturePercent);
    Serial.println(" %");

    if (soilMoisturePercent <= 10)
    {
        ledFlip(MOIST_LED);
        Serial.println("Soil to dry.");
    }
    else
    {
        digitalWrite(MOIST_LED, LOW);
    }
}

/*     WATER LEVEL    */
void waterAlert()
{
    if    (digitalRead(WATER_SENSOR) == HIGH)  
    {
        ledFlip(WATER_LED);
        Serial.println("No water");
    }
    else
    {
        digitalWrite(WATER_LED, LOW);
        Serial.println("Water OK");
    }
}
