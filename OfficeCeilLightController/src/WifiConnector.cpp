#include "WifiConnector.h"

WifiConnector::WifiConnector() = default;

void WifiConnector::connect()
{
    if (!WiFi.config(staticIP, gateway, subnet, dns, dns)) {
        Serial.println("Wifi config failed :(");
    }

    WiFiClass::mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    WiFi.waitForConnectResult();
}

void onWifiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    ESP.restart();
}

void WifiConnector::activateDisconnectHandler()
{
    WiFi.onEvent(onWifiDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
}
