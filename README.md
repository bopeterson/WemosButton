# WemosButton
Arduino library to make it easy to use buttons on Wemos and other ESP8266-based boards

Download and put WemosButton-folder + files in Arduino/Libraries

Include in your skecth with 

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
