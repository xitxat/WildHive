#include <Arduino.h>

#include "SensorsWildHive.h"

/* LEDs      */
int ledState = LOW;     // YELLOW Soil
int blueLedState = LOW; // BLUE   Water
int pirState = LOW;     // WHITE. Motion by default no motion detected

/* Moisture sensor calibration */
const int AirValue = 600;   // Dry  2% @580
const int WaterValue = 300; // Wet 98% @250 immersion value
int soilMoistureValue = 0;
int soilMoisturePercent = 0;
int pirVal = 0;                 // variable to store PIR sensor status (value)

/*     BLINK    */
void ledFlip(int pin)              //  BLUE led for water
{                                  //  Yellow led for moisture                     
         digitalWrite(pin , HIGH);
         delay(200);
         digitalWrite(pin , LOW);
         delay(200);
}

/*     MOISTURE    */
void soilAlert()
{
    soilMoistureValue = analogRead(A0); // NodeMcu only 1 ADC (A0)
    Serial.print("Analog Pin reading soil moisture value : ");
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
    Serial.println(" ");
}

/*     WATER LEVEL    */
void waterAlert()
{
    if    (digitalRead(WATER_SENSOR) == HIGH)  
    {
        ledFlip(WATER_LED);
        Serial.println("No water");
        Serial.println(" ");
    }
    else
    {
        digitalWrite(WATER_LED, LOW);
        Serial.println("Water OK");
        Serial.println(" ");
    }
}

/*     PIR    */
void detectMotion()
{
   pirVal = digitalRead(PIR_SENSOR); // read sensor value
   Serial.println("Checking motion detector...");
   Serial.print("PIR value  ");
   Serial.println(pirVal);

   if (pirVal == HIGH)
   {                               // check if the sensor is HIGH
      digitalWrite(PIR_LED, HIGH); // turn LED ON
      Serial.println("Motion detected!");
      delay(100);
   }
   else
   {
      digitalWrite(PIR_LED, LOW); // turn LED OFF
      Serial.println("Motion stopped!");
      pirState = LOW; // update variable state to LOW
      delay(200);     
   }
   Serial.println("");
}

