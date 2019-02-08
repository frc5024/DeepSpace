//! Operator Interface allows various commands to access the xbox controllers through the DriverStation
#ifndef _OI_HG_
#define _OI_HG_

#include <frc/WPILib.h>

class OI {
 public:
  OI(); //!< Class constructor
  
  /**
   * Function for getting the Driver's joystick data
   *
   * @return Pointer to the driver's joystick
   */
  frc::XboxController* GetJoystickDrive(void);
  
  /**
   * Function for getting the Operator's joystick data
   *
   * @return Pointer to the operator's joystick
   */
	frc::XboxController* GetJoystickOperator(void);

private:
	frc::XboxController* pJoystickDrive;    //!< Pointer for Driver's joystick
	frc::XboxController* pJoystickOperator; //!< Pointer for Operator's joystick
	frc::XboxController* pJoystickDebug;    //!< Pointer for Debug joystick
};

#endif // _OI_HG_