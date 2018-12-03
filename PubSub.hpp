#ifndef PubSub_hpp
#define PubSub_hpp

#include <Arduino.h>
#include <ESP8266WiFi.h>

void PubSub_setup(void (*function)(), char*, char*);
void PubSub_loop();
void PubSub_close();

#endif
