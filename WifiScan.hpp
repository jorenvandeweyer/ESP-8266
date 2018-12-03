#ifndef WifiScan_hpp
#define WifiScan_hpp

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WifiScan {
    public:
        WifiScan();
        String scan();
    private:
        int size;
        String result;
};

#endif
