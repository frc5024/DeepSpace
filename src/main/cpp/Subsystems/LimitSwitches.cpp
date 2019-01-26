#include "Subsystems/LimitSwitches.h"
#include "Robot.h"
#include "RobotMap.h"

LimitSwitches::LimitSwitches() : Subsystem("LimitSwitches") {
  // Initalize the limit switches used on the robot:
  this->limitSwitch1 = new frc::DigitalInput(1);
  this->limitSwitch2 = new frc::DigitalInput(2);
}

void LimitSwitches::InitDefaultCommand() {
  SetDefaultCommand(new DriveWithJoystick()); // TODO: this should be changed
}

bool LimitSwitches::isOn1() {
  return this->limitSwitch1->Get();
}

bool LimitSwitches::isOn2() {
    return this->limitSwitch2->Get();;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
