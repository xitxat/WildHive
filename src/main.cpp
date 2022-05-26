#include <Arduino.h>


  //  Blink test 
int ledState = LOW;                 //  Onboard LED OFF
unsigned long previousMillis = 0;
const long interval = 200;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

void blinkTest(){
    unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;  // Note that this switches the LED *off*
    } else {
      ledState = LOW;  // Note that this switches the LED *on*
    }
    digitalWrite(LED_BUILTIN, ledState);
  }
}


// the loop function runs over and over again forever
void loop() {
blinkTest();
}