#include "OI.h"
#include "RobotMap.h"

OI::OI() {
  this->pJoystickDrive    = new XboxController(XBOX_CONTROLLER_DRIVE_PORT);
	this->pJoystickOperator = new XboxController(XBOX_CONTROLLER_OPERATOR_PORT);
}

frc::XboxController* OI::GetJoystickDrive() {
	return this->pJoystickDrive;
}

frc::XboxController* OI::GetJoystickOperator() {
	return this->pJoystickOperator;
}