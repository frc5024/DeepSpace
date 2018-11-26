#ifndef _OI_HG_
#define _OI_HG_

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

#endif // _OI_HG_