#include "EEPROM_Str.hpp"

int address = 0;
byte value;
EEPROM_Str EPR(512);

void setup() {
  Serial.begin(115200);
  while (!Serial) { };
  delay(3000);
  EPR.print();
  char name[] = "joren";
  char message[] = "hello";
  EPR.add(name, message);
  EPR.print();
  EPR.clear();
}

void loop() {
  Serial.println(".");
  delay(1000);
}
