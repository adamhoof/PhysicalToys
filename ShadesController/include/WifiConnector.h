#pragma once

#include "WiFi.h"

const char WIFI_SSID[] = "Gei";
const char WIFI_PASSWORD[] = "1234567890";

class WifiConnector
{
private:
    const IPAddress staticIP {192, 168, 1, 155};
    const IPAddress gateway {192, 168, 1, 1};
    const IPAddress subnet {255, 255, 255, 0};
    const IPAddress dns {192, 168, 1, 1};
public:
    WifiConnector();

    void connect();

    void activateDisconnectHandler();
};
