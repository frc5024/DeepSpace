//! Main robot class that is called by wpilib
#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/TimedRobot.h>
#include <frc/WPILib.h>
#include <cscore_oo.h>

#include "Commands/TriggerDrive.h"
#include "OI.h"
#include "Subsystems/DriveTrain.h"

struct RobotPosition
{
	typedef enum
	{
		UPPER_LEFT   = 1,
		LOWER_LEFT   = 2,
		CENTER       = 3,
		UPPER_RIGHT  = 4,
		LOWER_RIGHT  = 5
	} Type;
};

struct HatchPosition
{
	typedef enum
	{
		BACK   = 10,
		MIDDLE = 20,
		FRONT  = 30
	} Type;
};

struct AutonomousType
{
	typedef enum
	{
		DRIVE_CONTROLLED                  = 100,
		TIMED_JUST_DRIVE_FORWARD          = 200,
		MOTION_PROFILE_JUST_DRIVE_FORWARD = 300,
		TOTAL_AUTONOMOUS                  = 400
	} Type;
};

class Robot : public frc::TimedRobot {
 public:
	// Subsystems
  static DriveTrain *m_DriveTrain; //!< Pointer for the DriveTrain
  static OI *m_oi;                 //!< Pointer for the Operator Interface (OI)

	// Commands
  TriggerDrive* pTriggerDrive; //!< Pointer for the TriggerDrive command

	// Robot methods
  void RobotInit() override;          //!< Runs once on robot boot
  void RobotPeriodic() override;      //!< Runs in a loop while the robot is turned on in any mode
  void DisabledInit() override;       //!< Runs once every time the robot is disabled
  void DisabledPeriodic() override;   //!< Runs in a loop while the robot is disabled
  void AutonomousInit() override;     //!< Runs once at the start of auto. Usually while the announcer starts counting down from 3
  void AutonomousPeriodic() override; //!< Runs in a loop during auto
  void TeleopInit() override;         //!< Runs once at the start of teleop when the bell sounds
  void TeleopPeriodic() override;     //!< Runs in a loop during teleop
  void TestPeriodic() override;       //!< Runs in a loop during test mode

 private:
  // Define cameras
  cs::UsbCamera frontCam; //!< Variable for the front camera
  cs::UsbCamera backCam;  //!< Variable for the Back camera

  // Autonomous Functions and Options
	int GetAutoType();
  frc::SendableChooser<int> scRobotPosition;
  frc::SendableChooser<int> scHatchPosition;
  frc::SendableChooser<int> scAutonomousType;
	frc::Command* pAutonomousCommand;
};

#endif //_ROBOT_HG_