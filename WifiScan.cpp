#include "WifiScan.hpp"

WifiScan::WifiScan() {

}

String WifiScan::scan() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    
    int total = WiFi.scanNetworks(false, true);

    String result;

    for (int i = 0; i < total; i++) {
        result += WiFi.SSID(i);
        result += ",";
        result += WiFi.encryptionType(i);
        result += ",";
        result += WiFi.RSSI(i);
        result += ",";
        result += WiFi.BSSIDstr(i);
        result += ",";
        result += WiFi.channel(i);
        result += ",";
        result += WiFi.isHidden(i);
        result += "\n";
    }

    Serial.println(result);
    return result;
}

