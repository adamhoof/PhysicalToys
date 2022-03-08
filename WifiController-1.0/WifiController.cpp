#include "WifiController.h"

WifiController::WifiController() = default;

WiFiClientSecure* WifiController::wiFiClientSecure()
{
    return &wifiClientSecure;
}

void WifiController::setTimeForCertValidation()
{
    time_t now;
    configTime(-5 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    now = time(nullptr);
    while (now < 1510592825) {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
}

void WifiController::setCertificates()
{
    setTimeForCertValidation();

    wifiClientSecure.setCACert(CA_CERT);
    wifiClientSecure.setCertificate(CLIENT_CERT);
    wifiClientSecure.setPrivateKey(CLIENT_KEY);
}

void WifiController::connect()
{
    WiFiClass::mode(WIFI_STA);

    String wifiHostname = "OfficeTableLamp";
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(wifiHostname.c_str());

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connecting to Wi-Fi");

    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        ESP.restart();
    }

    Serial.println("Wifi connected");
    Serial.println(WiFi.localIP());
}

void WifiController::disconnect()
{
    WiFi.disconnect();
}

void WifiController::maintainConnection()
{
    if (*wifiClientSecure.getSslFailedLoopCount() >= 20) {ESP.restart();}
    if (!WiFi.isConnected()) {
        disconnect();
        connect();
        delay(10);
    }
}
