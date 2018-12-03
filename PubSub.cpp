#include "PubSub.hpp"

void PubSub_close() {

}

void PubSub_setup(void (*function)(), char* ssid, char* pass) {
    Serial.println("---- THIS IS PUBSUB ----");
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("PASS: ");
    Serial.println(pass);
}

void PubSub_loop() {
    Serial.println("---- THIS IS PUBSUB LOOP ----");
    delay(2000);
}
