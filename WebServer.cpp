#include "WebServer.hpp"

WifiScan Scan = WifiScan();
ESP8266WebServer server(80);

String ssid;
String password;
String ScanResult;

void (*switchFunction)(char*, char*);

void initializeAP() {
    WiFi.softAP("testAP");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
}

void handleRoot() {
    server.send(200, "text/html", "<!DOCTYPE html><html><head></head><body> <form action='/connect'> <div> <div> <input type='text' value='ssid'> </div><div> <input type='password' value='password'> </div><div> <input type='submit' value='submit'> </div></div></form></body></html>");
}

void handleScan() {
    server.send(200, "text/plain", ScanResult);
    ScanResult = Scan.scan();
    initializeAP();
}

void handleResults() {
    server.send(200, "text/plain", ScanResult);
}

void handleConnect() {
    if (!server.hasArg("ssid") || !server.hasArg("password")) {
        return server.send(200, "application/json", "{'s':false}");
    }

    ssid = server.arg("ssid");
    password = server.arg("password");

    Serial.print("ssid: ");
    Serial.println(ssid);
    Serial.print("password: ");
    Serial.println(password);
    server.send(200, "application/json", "{'s':true}");
    WebServer_close();
    switchFunction(&ssid[0], &password[0]);
}

void WebServer_close() {
    server.close();
}

void WebServer_setup(void (*function)(char*, char*)) {
    switchFunction = function;
    ScanResult = Scan.scan();

    initializeAP();
    server.on("/", handleRoot);
    server.on("/scan", handleScan);
    server.on("/results", handleResults);
    server.on("/connect", handleConnect);
    server.begin();
    Serial.println("HTTP server started");
}

void WebServer_loop() {
    server.handleClient();
}
