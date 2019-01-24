//! A subsystem that interfaces with the drivebase on the robot
#ifndef _CLIMBSONIC_HG_
#define _CLIMBSONIC_HG_

#include <frc/commands/Subsystem.h>
#include <frc/Ultrasonic.h>
#include "RobotMap.h"

class ClimbSonic : public frc::Subsystem {
 public:
  ClimbSonic(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (DriveWithJoystick)
	
	/**
	 * Get the distance reported by the sensor
	 *
	 * @return Distance in MM
	 */
  double GetDistance();

 private:
  frc::Ultrasonic *sensor //!< The ultrasonic sensor
};

#endif // _CLIMBSONIC_HG_