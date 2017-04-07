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

#if WEMBUT_DEBUG
int WemosButton::_lastPressedNumber = -1;
#endif

WemosButton::WemosButton() {
    _buttonState = NOTPRESSED;
    _lastButtonState = NOTPRESSED; //note: this is the last *stable* state
    _lastStateSwitchTime = 0;
    _lastPressTime = 0;
    _onHold = false;
}

void WemosButton::begin(int pin) {
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP); //active low
    //pinMode(_pin,INPUT);
    reading = digitalRead(_pin);
    _buttonState = reading;
    _lastButtonState = _buttonState; //note: this is the last *stable* state
}

bool WemosButton::readButton() {
    return readButtonAdvanced(0) & PRESS_DETECTED;
}

byte WemosButton::readButtonAdvanced(unsigned long holdTime) {
    //detects press, release and hold
    //button connected to pullup and ground, ie LOW=PRESSED
    //holdTime is the time in ms that the button must be pressed for hold to be detected
    //holdTime = 0 means that hold is not detected at all. 
    unsigned long debounceDelay = 15;
    reading = digitalRead(_pin);
    byte pressDetected=false;
    byte releaseDetected=false;
    byte holdDetected=false;
    byte holdReleaseDetected=false;

    if (reading != _lastButtonState) {
        // reset the debouncing timer
        _lastStateSwitchTime = millis();
    }
    
    
    if ((millis() - _lastStateSwitchTime) > debounceDelay) {
        if (reading != _buttonState) {
            //stable state change detected
            _buttonState = reading;
            if (_buttonState == PRESSED) {
                //stable press detected
                pressDetected=true;
                _lastPressTime = millis();
            } else {
                //stable release detected
                releaseDetected=true;
                if (_onHold) {
                    holdReleaseDetected=true;
                    _onHold=false;
                }
            }
        }
    }
    
    if ((millis() - _lastPressTime) > holdTime && holdTime != 0) {
        if (_buttonState == PRESSED && !_onHold) {
            //_lastHoldTime=millis();
            _onHold = true;
            holdDetected=true;
        }
    }
    _lastButtonState = reading;

#if WEMBUT_DEBUG
    byte darray[]={D0,D1,D2,D3,D4,D5,D6,D7,D8};
    while (Serial.available()) {
        _lastPressedNumber = Serial.read()-48;
    }

    if (_lastPressedNumber>=0 && _lastPressedNumber<=8) {
        if (darray[_lastPressedNumber]==_pin) {
            pressDetected = true;
            _lastPressedNumber=-1;
        }
    }
#endif
    
    byte result = 0x00; //hex for 0000 0000
    if (pressDetected) {
        result |= PRESS_DETECTED; // turn on press detected bit
    }
    if (releaseDetected) {
        result |= RELEASE_DETECTED; // turn on release detected bit
    }
    if (holdDetected) {
        result |= HOLD_DETECTED; // turn on hold detected bit
    }
    if (holdReleaseDetected) {
        result |= HOLD_RELEASE_DETECTED; // turn on hold release detected bit
    }
    
    //put in bit pattern and return
    

    return result;
}

