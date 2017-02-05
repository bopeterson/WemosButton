/*
   connections

   D6 to Ground: push button
*/


#include <WemosButton.h>

WemosButton button;

void setup() {
  button.begin(D6);
  Serial.begin(9600);
}

void loop() {
 unsigned long currentMillis = millis();

  byte buttonStatus=button.readButtonAdvanced(10000);
  if (buttonStatus & button.PRESS_DETECTED) {
    Serial.println("button pressed");
  }
  if (buttonStatus &button.RELEASE_DETECTED) {
    Serial.println("button released");
  }
  if (buttonStatus & button.HOLD_RELEASE_DETECTED) {
    Serial.println("button released from hold");
  }
  if (buttonStatus & button.HOLD_DETECTED) {
    Serial.println("button held");
  } 
}

