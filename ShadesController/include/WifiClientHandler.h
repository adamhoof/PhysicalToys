#pragma once

#include "WiFi.h"

const char WIFI_SSID[] = "Gei";
const char WIFI_PASSWORD[] = "1234567890";

class WifiClientHandler
{
public:
    WifiClientHandler();

    void connect();

    void maintainConnection();

    void disconnect();
};
