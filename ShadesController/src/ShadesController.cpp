#include "ShadesController.h"

PhysicalToyController::ShadesController::ShadesController() = default;

void PhysicalToyController::ShadesController::open(MQTTClientHandler& mqttClientHandler,
                                                   StepperMotorController& motorController)
{
    mqttClientHandler.publish("Set: open");
    mqttClientHandler.disconnect();

    while (digitalRead(32)) {
        motorController.stepperMotor.antiClockwiseStep();
    }

    motorController.setCurrPos(1);

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

    motorController.setCurrPos(0);


    mqttClientHandler.reconnect();
}
