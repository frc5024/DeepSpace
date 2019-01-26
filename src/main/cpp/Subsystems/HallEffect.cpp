#include "Subsystems/HallEffect.h"
#include "Robot.h"
#include "RobotMap.h"

HallEffect::HallEffect() : Subsystem("HallEffect") {}

void HallEffect::InitDefaultCommand() {
  //Set the default command for a subsystem here.
   SetDefaultCommand(new DriveWithJoystick());
}