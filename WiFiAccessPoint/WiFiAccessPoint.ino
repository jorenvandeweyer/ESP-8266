/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "ESPap";
const char *password = "joren123";

int channelId;
String channelPassword;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send(200, "text/html", "<!DOCTYPE html><html><head></head><body> <form action='/connect'> <div> <div> <input type='text' value='id'> </div><div> <input type='password' value='password'> </div><div> <input type='submit' value='submit'> </div></div></form></body></html>");
}

void connect() {
  if (!server.hasArg("id") || !server.hasArg("password")) {
    return server.send(200, "application/json", "{'s':false}");
  }
  channelId = server.arg("id").toInt();
  channelPassword = server.arg("password");
  Serial.print("channel: ");
  Serial.println(server.arg("id"));
  Serial.print("password: ");
  Serial.println(server.arg("password"));
  return server.send(200, "application:json", "{'s':true}");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/connect", connect);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

