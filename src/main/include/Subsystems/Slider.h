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

  void Center(); //!< Centers the slider
 private:
  double sliderSide;
  can::WPI_TalonSRX* pSliderMotor; //!< Pointer for the slider motor
  frc::DigitalInput* pLeftHall; //!< Pointer to the left hall sensor for the slider
  frc::DigitalInput* pRightHall; //!< Pointer to the right hall sensor for the slider
  frc::DigitalInput* pCenterHall; //!< Pointer to the center hall sensor for the slider
  std::shared_ptr<NetworkTable> ntTelemetry; //!< A pointer to the /SmartDashboard/Telemetry table
};

#endif // _Slider_HG_