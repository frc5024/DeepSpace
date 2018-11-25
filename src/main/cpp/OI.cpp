/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

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