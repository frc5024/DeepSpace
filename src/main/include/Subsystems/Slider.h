//! A subsystem that interfaces with the drivebase on the robot
#ifndef _Slider_HG_
#define _Slider_HG_

#include <frc/commands/Subsystem.h>
#include <networktables/NetworkTable.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "RobotMap.h"
#include <Commands/ControlSlider.h>
#include <frc/DigitalInput.h>

class Slider : public frc::Subsystem {
 public:
  Slider(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (ControlSlider)
	
	/**
	 * Pass data to motor
	 *
	 * @param speed Slider speed (form -1 to 1)
	 */
  void Slide(double speed);

  void Center();
 private:
  double sliderSide;
  can::WPI_TalonSRX* pSliderMotor; //!< Pointer for the slider motor
  frc::DigitalInput* pLeftHall;
  frc::DigitalInput* pRightHall;
  frc::DigitalInput* pCenterHall;
  std::shared_ptr<NetworkTable> ntTelemetry; //!< A pointer to the /SmartDashboard/Telemetry table
};

#endif // _Slider_HG_