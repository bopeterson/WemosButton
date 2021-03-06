# WemosButton
Arduino library to make it easy to use buttons on Wemos and other ESP8266-based boards

Download and put WemosButton-folder + files in Arduino/Libraries

Include the library in your sketch with

```cpp
#include "WemosButton.h"
```

## Available pins on Wemos

The pins on the Wemos-boards can be used without external pull up resistors in the following modes:

- pinMode(Dx,INPUT_PULLUP), x=1, 2, 3, 4, 5, 6, 7, active low (pull up on chip)
- pinMode(Dx,INPUT), x=3,4 active low (pull up on board)
- pinMode(Dx,INPUT), x=8 active high (pull down on board)
- pinMode(Dx,INPUT_PULLDOWN_16), x=0, active high (pull down on chip)
- Pin D1 and D2 are used with the OLED display and can not be used as inputs together with OLED display
- Pin D4 is connected to BUILTIN_LED and can be used but will make the LED flash when the button is pressed

This leaves pins D3, D5, D6 and D7 available for INPUT_PULLUP without affecting OLED or BUILTIN_LED. D0 and D8 can be used with INPUT_PULLDOWN_16 and INPUT respectively if additional inputs are needed

## How to use

There are two methods, `readButton()` and `readButtonAdvanced()` that are available. `readButton()` is the simple one that only detects when a button is pressed. `readButtonAdvanced()` also detects when a button is released and held pressed for a configurable time, or double clicked. See examples for more info.

## Debug modes

If WEMBUT_DEBUG is defined TRUE in WemosButton.h, the serial monitor can be used to emulate button presses (just simple press, not hold nor double click). Enter digit 0 to 8 and send to emulate button D0 to D8 being pressed. 
