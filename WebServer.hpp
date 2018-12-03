#ifndef WebServer_hpp
#define WebServer_hpp

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "WifiScan.hpp"

void initializeAP();
void handleRoot();
void handleScan();
void handleResults();
void handleConnect();
void WebServer_setup(void (*function)(char*, char*));
void WebServer_loop();
void WebServer_close();

#endif
