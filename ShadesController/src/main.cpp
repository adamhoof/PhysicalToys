#include <Arduino.h>
#include <MQTTClientHandler.h>
#include <WifiConnector.h>
#include <OTAHandler.h>
#include "StepperMotorController.h"

#define ALLOW_PIN 2

MQTTClientHandler mqttClientHandler {};
WifiConnector wifiConnector {};
OTAHandler otaHandler {};

PhysicalToyController::StepperMotorController stepperMotorController{};

void setup() {

    pinMode(ALLOW_PIN, OUTPUT);

    stepperMotorController.stepperMotor.setupPins(16, 17, 18, 19);

    Serial.begin(115200);
}

void loop() {
    /*if (!digitalRead(ALLOW_PIN)){
      return;
    }*/
    stepperMotorController.moveMotor(CLOCKWISE);
    Serial.println(stepperMotorController.stepCount);
    delay(5000);
    stepperMotorController.moveMotor(ANTI_CLOCKWISE);
    Serial.println(stepperMotorController.stepCount);
}
