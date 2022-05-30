#include <Arduino.h>

#include "SensorsWildHive.h"

/* Millis      */
unsigned long previousMillis = 0; // will store last time LED was updated
const long interval = 200;        // interval at which to blink (milliseconds)
const long blinkWaterLevel = 200;        // interval at which to blink (milliseconds)

/* LEDs      */
int ledState = LOW; // ledState used to set the LED

/* Moisture sensor calibration */
const int AirValue = 600;   // Dry  2% @580
const int WaterValue = 300; // Wet 98% @250 immersion value
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

/*     MOISTURE    */

void moistureCap()
{
    soilMoistureValue = analogRead(A0); // NodeMcu only 1 ADC (A0)
    Serial.print("Analog Pin reading: ");
    Serial.println(soilMoistureValue);

    soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    Serial.print("Soil moisture ");
    Serial.print(soilmoisturepercent);
    Serial.println(" %");

    if (soilmoisturepercent <= 10)
    {
        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= interval)
        {
            // save the last time you blinked the LED
            previousMillis = currentMillis;

            // if the LED is off turn it on and vice-versa:
            if (ledState == LOW)
            {
                ledState = HIGH;
            }
            else
            {
                ledState = LOW;
            }

            // set the LED with the ledState of the variable:
            digitalWrite(MOIST_LED, ledState);
        }
        Serial.println("Soil to dry.");
    }
    else
    {
        digitalWrite(MOIST_LED, LOW);
    }

}





