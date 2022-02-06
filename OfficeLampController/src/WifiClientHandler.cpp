#include "WifiClientHandler.h"

WifiClientHandler::WifiClientHandler() = default;

void WifiClientHandler::connect()
{
    /*WiFi.persistent(false);*/
    WiFiClass::mode(WIFI_STA);

    String wifiHostname = "OfficeTableLamp";
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(wifiHostname.c_str());

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connecting to Wi-Fi");

    WiFi.waitForConnectResult();

    Serial.println("Wifi connected");
    Serial.println(WiFi.localIP());
}

void WifiClientHandler::maintainConnection()
{
    if (!WiFi.isConnected()) {
        ESP.restart();
    }
}

void WifiClientHandler::disconnect()
{
    WiFi.disconnect();
}
