#include <WemosButton.h>

WemosButton b1;
WemosButton b2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  b1.begin(D6);
  b2.begin(D7);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (b1.readButton()) {
    Serial.println("button 1 pressed");
  }
  if (b2.readButton()) {
    Serial.println("button 2 pressed");
  }

  
  delay(10);

}
