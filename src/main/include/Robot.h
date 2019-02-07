//! Main robot class that is called by wpilib
#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <networktables/NetworkTable.h>
#include <frc/TimedRobot.h>
#include <frc/WPILib.h>
#include <cscore_oo.h>

#include "Commands/TriggerDrive.h"
#include "Commands/ControlCompressor.h"
#include "Commands/testUltra.h"
#include "Commands/PullArm.h"
#include "Commands/PullLeg.h"
#include "Commands/DeployClimb.h"
#include "Commands/DropCargo.h"
#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/CrawlDrive.h"
#include "Subsystems/Arm.h"
#include "Subsystems/Leg.h"
#include "Subsystems/Cargo.h"
#include "Commands/ControlSlider.h"
#include "Subsystems/Slider.h"
#include "Subsystems/Compressor.h"
#include "Subsystems/Piston.h"

#include <frc/PowerDistributionPanel.h>
#include <frc/DriverStation.h>


class Robot : public frc::TimedRobot {
 public:
	// Subsystems
  static Compressor *m_Compressor; //!< Pointer for the Compressor
  static DriveTrain *m_DriveTrain; //!< Pointer for the DriveTrain
  static Piston *m_Piston;         //!< Pointer for the Piston
  static CrawlDrive *m_CrawlDrive; //!< Pointer for the DriveTrain
  static Arm *m_Arm;               //!< Pointer for the Arm
  static Leg *m_Leg;               //!< Pointer for the Leg
  static OI *m_oi;                 //!< Pointer for the Operator Interface (OI)
  static Slider *m_Slider;         //!< Pointer for the Slider
  static Cargo *m_Cargo;           //!< Pointer for the Cargo

	// Commands
  TriggerDrive* pTriggerDrive; //!< Pointer for the TriggerDrive command
  testUltra* pTestUltra;
  PullArm* pPullArm;
  PullLeg* pPullLeg;
  DeployClimb* pDeployClimb;
  ControlSlider* pControlSlider; //!< Pointer for the ControlSlider command
  ControlCompressor* pControlCompressor; //!< Pointer for the ControlCompressor command
  DropCargo* pDropCargo;

	// Robot methods
  void RobotInit()          override; //!< Runs once on robot boot
  void RobotPeriodic()      override; //!< Runs in a loop while the robot is turned on in any mode
  void DisabledInit()       override; //!< Runs once every time the robot is disabled
  void DisabledPeriodic()   override; //!< Runs in a loop while the robot is disabled
  void AutonomousInit()     override; //!< Runs once at the start of auto. Usually while the announcer starts counting down from 3
  void AutonomousPeriodic() override; //!< Runs in a loop during auto
  void TeleopInit()         override; //!< Runs once at the start of teleop when the bell sounds
  void TeleopPeriodic()     override; //!< Runs in a loop during teleop
  void TestPeriodic()       override; //!< Runs in a loop during test mode

 private:
  // Define cameras
  cs::UsbCamera frontCam;  //!< Variable for the front camera
  cs::UsbCamera visionCam; //!< Variable for the Vision camera

  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  // MyAutoCommand m_myAuto;
  frc::SendableChooser<frc::Command*> m_chooser;

  frc::DriverStation& driverStation = frc::DriverStation::GetInstance(); //!< DriverStation instance
  frc::PowerDistributionPanel* pdp; //!< Power Distrobution Panel information

  std::shared_ptr<NetworkTable> ntTelemetry; //!< A pointer to the /SmartDashboard/Telemetry table
};

#endif //_ROBOT_HG_