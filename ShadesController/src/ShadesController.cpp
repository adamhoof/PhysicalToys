#include "ShadesController.h"

PhysicalToyController::ShadesController::ShadesController() = default;

void PhysicalToyController::ShadesController::open(MQTTClientHandler& mqttClientHandler,
                                                   StepperMotorController& motorController)
{
    mqttClientHandler.publish("Set: open");
    mqttClientHandler.disconnect();

    for (uint16_t i = 0; i < 10000; ++i) {
        motorController.stepperMotor.antiClockwiseStep();
    }

    motorController.setCurrPos(OPEN);

    if (WiFiClass::status() == WL_DISCONNECTED) {
        WiFi.reconnect();
    }

    mqttClientHandler.reconnect();
}

void PhysicalToyController::ShadesController::close(MQTTClientHandler& mqttClientHandler,
                                                    StepperMotorController& motorController)
{
    mqttClientHandler.publish("Set: close");
    mqttClientHandler.disconnect();

    while (digitalRead(32)) {
        motorController.stepperMotor.clockwiseStep();
    }
    motorController.leaveSwitchAlone();

    motorController.setCurrPos(CLOSE);

    if (WiFiClass::status() == WL_DISCONNECTED) {
        WiFi.reconnect();
    }

    mqttClientHandler.reconnect();
}
