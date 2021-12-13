#include "ShadesController.h"

PhysicalToyController::ShadesController::ShadesController() = default;

void PhysicalToyController::ShadesController::open(MQTTClientHandler& mqttClientHandler,
                                                   StepperMotorController& motorController)
{
    for (uint16_t i = 0; i < 30; ++i) {
        for (int j = 0; j < 500; ++j) {
            motorController.stepperMotor.antiClockwiseStep();
        }
        mqttClientHandler.maintainConnection();
    }
}

void PhysicalToyController::ShadesController::close(MQTTClientHandler& mqttClientHandler,
                                                    StepperMotorController& motorController)
{
    motorController.calibrate();
}
