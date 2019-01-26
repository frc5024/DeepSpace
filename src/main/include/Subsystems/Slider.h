//! A subsystem that interfaces with the drivebase on the robot
#ifndef _Slider_HG_
#define _Slider_HG_

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "RobotMap.h"
#include <Commands/ControlSlider.h>

class Slider : public frc::Subsystem {
 public:
  Slider(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (DriveWithJoystick)
	
	/**
	 * Pass data to motor
	 *
	 * @param speed Slider speed (form -1 to 1)
	 */
  void Slide(double speed);

 private:
  can::WPI_TalonSRX* pSliderMotor; //!< Pointer for left front motor
};

#endif // _Slider_HG_