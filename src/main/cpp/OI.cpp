#include "OI.h"
#include "RobotMap.h"

OI::OI() {
  this->pJoystickDrive    = new frc::XboxController(XBOX_CONTROLLER_DRIVE_PORT);
	this->pJoystickOperator = new frc::XboxController(XBOX_CONTROLLER_OPERATOR_PORT);
	this->pJoystickDebug    = new frc::XboxController(XBOX_CONTROLLER_DEBUG_PORT);
}

frc::XboxController* OI::GetJoystickDrive() {
	return this->pJoystickDrive;
}

frc::XboxController* OI::GetJoystickOperator() {
	return this->pJoystickOperator;
}

frc::XboxController* OI::GetJoystickDebug(){
  return this->pJoystickDebug;
}