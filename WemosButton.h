#ifndef WemosButton_h
#define WemosButton_h

#include "Arduino.h"

class WemosButton {
  public:
    WemosButton();
    void begin(int pin);
    bool readButton(); 

  private:
    int _buttonState;
    int _lastButtonState;
    unsigned long _lastDebounceTime;
    int _pin;
};
#endif

