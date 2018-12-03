#include "PubSub.hpp"

bool FLOW = 0;

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
    FLOW = !FLOW;
    digitalWrite(13, FLOW);
    Serial.println("---- THIS IS PUBSUB LOOP ----");
    Serial.print("LED IS NOW: ");
    Serial.println(FLOW);
    delay(2000);
}
