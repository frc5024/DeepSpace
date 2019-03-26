//! Main robot class that is called by wpilib
#ifndef _ROBOT_HG_
#define _ROBOT_HG_

// FRC
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/TimedRobot.h>
#include <frc/WPILib.h>
#include <cscore_oo.h>
#include <iostream>
#include <networktables/NetworkTable.h>

// Commands
#include "Commands/TriggerDrive.h"
#include "Commands/ControlCompressor.h"
#include "Commands/PullArm.h"
#include "Commands/PullLeg.h"
#include "Autonomous/AutoClimbHigh.h"
#include "Commands/ClimbManager.h"
#include "Commands/ControlHatchGripper.h"
#include "Commands/ControlLight.h"
#include "Commands/Climb.h"
#include "Commands/ControlSlider.h"
#include "Commands/ControlCargo.h"

// Interfaces
#include "OI.h"

// Subsystems
#include "Subsystems/DriveTrain.h"
#include "Subsystems/CrawlDrive.h"
#include "Subsystems/Arm.h"
#include "Subsystems/Leg.h"
#include "Subsystems/Slider.h"
#include "Subsystems/Compressor.h"
#include "Subsystems/Piston.h"
#include "Subsystems/HatchGripper.h"
#include "Subsystems/Flap.h"
#include "Subsystems/Light.h"

// Telemetry devices
#include <frc/PowerDistributionPanel.h>
#include <frc/DriverStation.h>
#include "AHRS.h"

class Robot : public frc::TimedRobot {
 public:

	// Subsystems
  static cCompressor  *m_cCompressor;  //!< Pointer for the cCompressor
  static DriveTrain   *m_DriveTrain;   //!< Pointer for the DriveTrain
  static Piston       *m_Piston;       //!< Pointer for the Piston
  static CrawlDrive   *m_CrawlDrive;   //!< Pointer for the DriveTrain
  static Arm          *m_Arm;          //!< Pointer for the Arm
  static Leg          *m_Leg;          //!< Pointer for the Leg
  static OI           *m_oi;           //!< Pointer for the Operator Interface (OI)
  static Slider       *m_Slider;       //!< Pointer for the Slider
  static HatchGripper *m_HatchGripper; //!< Pointer for the Hatch Gripper
  static Flap         *m_Flap;         //!< Pointer for the Cargo Flap
  static Light        *m_Light;        //!< Pointer for the Light

	// Commands
  TriggerDrive        *pTriggerDrive;        //!< Pointer for the TriggerDrive command
  PullArm             *pPullArm;             //!< Pointer for the arm debugging command
  PullLeg             *pPullLeg;             //!< Pointer for the leg debugging command
  ControlHatchGripper *pControlHatchGripper; //!< Pointer for the finger control command
  ControlSlider       *pControlSlider;       //!< Pointer for the ControlSlider command
  ControlCompressor   *pControlCompressor;   //!< Pointer for the ControlCompressor command
  ControlCargo        *pControlCargo;        //!< Pointer for the cargo control command
  ControlLight        *pControlLight;        //!< Pointer for the vision light control command
  ClimbManager        *pClimbManager;        //!< Pointer for the climb management command
  AutoClimbHigh       *pAutoClimbHigh;       //!< Pointer for the auto high climb command
  Climb               *pClimb;               //!< Pointer for the climb control command

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
  void SharedPeriodic();              //!< Runs during teleop and auto
  void SharedInit();                  //!< Used to initalize commands for both auto and teleop. (2019 only)

private:
  // Define cameras
  cs::UsbCamera frontCam;  //!< Variable for the front camera
  cs::UsbCamera visionCam; //!< Variable for the Vision camera

  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  // MyAutoCommand m_myAuto;
  frc::SendableChooser<frc::Command*> m_chooser;

  frc::DriverStation& driverStation = frc::DriverStation::GetInstance(); //!< DriverStation instance
  // frc::PowerDistributionPanel* pdp; //!< Power Distrobution Panel information

  std::shared_ptr<NetworkTable> ntTelemetry; //!< A pointer to the /SmartDashboard/Telemetry table

  AHRS* pGyro;
};

#endif //_ROBOT_HG_