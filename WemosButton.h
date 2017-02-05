#ifndef WemosButton_h
#define WemosButton_h

#define WEMBUT_DEBUG true
//Serial.begin(baudrate) required in setup() of Arduino sketch if WEMBUT_DEBUG is true
//pressed button can be emulated by sending 0 - 8 in serial monitor if WEMBUT_DEBUG is true

#if WEMBUT_DEBUG
    #define wembut_debugprint(...) Serial.print(__VA_ARGS__)
    #define wembut_debugprintln(...) Serial.println(__VA_ARGS__)
#else
    #define wembut_debugprint(...)
    #define wembut_debugprintln(...)
#endif

#include "Arduino.h"

class WemosButton {
  public:
    WemosButton();
    void begin(int pin);
    
    bool readButton();
    byte readButtonAdvanced(unsigned long holdTime);
    
    byte reading;
    
    //assumes buttons with pull up and active low. Used like constants now, but might be 
    //used as variablea in the future if active high will be supported
    byte PRESSED = LOW;
    byte NOTPRESSED = HIGH;
    
    //bitmask constants
    const byte PRESS_DETECTED = 0x01; // hex for 0000 0001
    const byte RELEASE_DETECTED = 0x02; // hex for 0000 0010
    const byte HOLD_DETECTED = 0x04; // hex for 0000 0100
    const byte HOLD_RELEASE_DETECTED = 0x08; // hex for 0000 1000

  private:
    byte _buttonState;
    byte _lastButtonState;
    unsigned long _lastStateSwitchTime;
    unsigned long _lastPressTime;
    byte _onHold;
    
    
    int _pin;
#if WEMBUT_DEBUG
    static int _lastPressedNumber;
#endif
};
#endif

