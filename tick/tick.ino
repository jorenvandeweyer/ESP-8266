#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Tick");
  delay(1000);
}
