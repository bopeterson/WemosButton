#include "Arduino.h"
#include "WemosButton.h"

/* 

For the Wemos:

The pins can be used without external pull up resistors in the following modes:
pinMode(Dx,INPUT_PULLUP), x=1, 2, 3, 4, 5, 6, 7, active low (pull up on chip)
pinMode(Dx,INPUT), x=3,4 active low (pull up on board)
pinMode(Dx,INPUT), x=8 active high (pull down on board)
pinMode(Dx,INPUT_PULLDOWN_16), x=0, active high (pull down on chip)

Pin D1 and D2 are used with the OLED display
Pin D4 is connected to BUILTIN_LED

This leaves pins D3, D5, D6 and D7 available for INPUT_PULLUP without affecting OLED or BUILTIN_LED. D0 and D8 can be used with INPUT_PULLDOWN_16 and INPUT if additional inputs are needed

*/

WemosButton::WemosButton() {
  _buttonState = HIGH;
  _lastButtonState = HIGH;
  _lastDebounceTime = 0;
}

void WemosButton::begin(int pin) {
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP); //active low
}

bool WemosButton::readButton() {
  //button connected to pullup and ground, ie LOW=PRESSED
  unsigned long debounceDelay = 50;
  int reading = digitalRead(_pin);
  int pressDetected=false;
  if (reading != _lastButtonState) {
    // reset the debouncing timer
    _lastDebounceTime = millis();
  }

  if ((millis() - _lastDebounceTime) > debounceDelay) {
    if (reading != _buttonState) {
      _buttonState = reading;
      if (_buttonState == LOW) {
        pressDetected=true;
      }
    }
  }
  _lastButtonState = reading;  
  return pressDetected;
}

