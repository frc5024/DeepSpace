#include "Subsystems/LimitSwitches.h"
#include "Robot.h"
#include "RobotMap.h"

LimitSwitches::LimitSwitches() : Subsystem("LimitSwitches") {
  // Initalize the limit switches used on the robot:
  this->limitSwitch1 = new frc::DigitalInput(LIMITSWITCH_ONE_PORT);
  this->limitSwitch2 = new frc::DigitalInput(LIMITSWITCH_TWO_PORT);
}

void LimitSwitches::InitDefaultCommand() {
  SetDefaultCommand(new LimitSwitchCommand()); // TODO: this should be changed
}

bool LimitSwitches::isOn1() {
  return this->limitSwitch1->Get();
}

int LimitSwitches::ChannelNumber() {
  return this->limitSwitch1->GetChannel();
}

bool LimitSwitches::isOn2() {
    return this->limitSwitch2->Get();
}