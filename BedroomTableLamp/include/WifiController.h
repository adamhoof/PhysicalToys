#pragma once

#include "WiFi.h"

const char WIFI_SSID[] = "Gei";
const char WIFI_PASSWORD[] = "1234567890";

class WifiController
{
private:
    const IPAddress staticIP {192, 168, 1, 161};
    const IPAddress gateway {192, 168, 1, 1};
    const IPAddress subnet {255, 255, 255, 0};
    const IPAddress dns {192, 168, 1, 1};
public:
    WifiController();

    void connect();

    void disconnect();
};
