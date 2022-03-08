#pragma once

#include "WiFiClientSecure.h"
#include "certs.h"

const char WIFI_SSID[] = "Gei";
const char WIFI_PASSWORD[] = "1234567890";

class WifiController
{
private:
    WiFiClientSecure wifiClientSecure {};
public:
    WifiController();

    WiFiClientSecure* wiFiClientSecure();

    void setTimeForCertValidation();

    void setCertificates();

    void connect();

    void maintainConnection();

    void disconnect();
};
