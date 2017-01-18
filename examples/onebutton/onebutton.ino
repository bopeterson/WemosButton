#include <WemosButton.h>

WemosButton b1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  b1.begin(D6);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (b1.readButton()) {
    Serial.println("press detected");
  }
  delay(10);

}
