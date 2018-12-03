#include "PubSub.hpp"

bool FLOW = 0;
long lastPing = 0;

WiFiClient wifiClient;
PubSubClient client(wifiClient);



void setup_wifi(char* ssid, char*password) {
    delay(10);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("Wifi Connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    String message;

    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println(message);

    if (strcmp(topic, "esp8266-led") == 0) {
        if ((char)payload[0] == '1') {
            digitalWrite(13, HIGH);
        } else {
            digitalWrite(13, LOW);
        }
    }
}

void reconnect() {
    while(!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        
        if (client.connect("arduinoClient", "esp", "joren123")) {
            Serial.println("connected");

            client.subscribe("esp8266-led");
            client.publish("presence", "esp");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");

            delay(5000);
        }
    }
}

void PubSub_close() {

}

void PubSub_setup(void (*function)(), char* ssid, char* pass) {
    setup_wifi(ssid, pass);
    client.setServer("dupbit.com", 1883);
    client.setCallback(callback);
    Serial.println("connecting to mqtt");
}

void PubSub_loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    long now = millis();

    if (now - lastPing > 5000) {
        lastPing = now;
        client.publish("ping", "esp");
    }
}
