#ifndef PubSub_hpp
#define PubSub_hpp

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

void setup_wifi(char*, char*);
void callback(char*, byte*, unsigned int);
void reconnect();
void PubSub_close();
void PubSub_setup(void (*function)(), char*, char*);
void PubSub_loop();

#endif
