#include "defines.h"

#include <ESP8266WiFi.h>
#include "EEPROM_Str.hpp"
#include "WebServer.hpp"
#include "PubSub.hpp"

EEPROM_Str EPR = EEPROM_Str(512);
int STATE = IDLE;

void checkHardReset() {
  if (digitalRead(GPC4)) {
    Serial.println("Clearing EEPROM");
    EPR.clear();
    Serial.println("EEPROM Cleared, lower GPC4");
  }
  while (digitalRead(GPC4)) {
    Serial.print(".");
    delay(3000);
  }
  Serial.println("");
}

void checkState() {
  if (EPR.hasKey("SSID") && EPR.hasKey("PASS")) {
    STATE = PUBSUB;
  } else {
    STATE = WEBSERVER;
  }
}

void enablePubSub(char* ssid, char* pass) {
  STATE = PUBSUB;
  EPR.add("SSID", ssid);
  EPR.add("PASS", pass);

  PubSub_setup(&enableWebServer, ssid, pass);
}

void enableWebServer() {
  STATE = WEBSERVER;
  WebServer_setup(&enablePubSub);
}

void setup() {
  pinMode(GPC4, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(115200);
  while (!Serial) { };

  checkHardReset();
  checkState();

  if (STATE == PUBSUB) {
    PubSub_setup(&enableWebServer, EPR.getString("SSID"), EPR.getString("PASS"));
  } else if (STATE == WEBSERVER) {
    WebServer_setup(&enablePubSub);
  }
}

void loop() {
  switch(STATE) {
    case WEBSERVER:
      WebServer_loop();
      break;
    case PUBSUB:
      PubSub_loop();
      break;
    default:
      Serial.println(".");
      break;
  }
}
