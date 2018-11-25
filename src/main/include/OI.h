#pragma once

#include <WPILib.h>

class OI {
 public:
  OI();
  frc::XboxController* GetJoystickDrive(void);
	frc::XboxController* GetJoystickOperator(void);

private:
	frc::XboxController* pJoystickDrive;
	frc::XboxController* pJoystickOperator;
};
