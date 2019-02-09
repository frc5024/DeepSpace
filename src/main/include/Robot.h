//! Main robot class that is called by wpilib
#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/TimedRobot.h>
#include <frc/WPILib.h>
#include <cscore_oo.h>

#include "Commands/TriggerDrive.h"
#include "Commands/LimitSwitchCommand.h"
#include "Commands/ToggleLight.h"
#include "Commands/HallEffectTest.h"
#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/HallEffect.h"
#include "Subsystems/UltrasonicDistance.h"
#include "Subsystems/LimitSwitches.h"

class Robot : public frc::TimedRobot {
 public:
	// Subsystems
  static DriveTrain *m_DriveTrain;  //!< Pointer for the DriveTrain
  static OI *m_oi;                  //!< Pointer for the Operator Interface (OI)
  static LimitSwitches *m_liSwitches; //!< Pointer for the Limit Switches
  static HallEffect *m_hEffect;       //!< Pointer for the Hall Effect
	
  // note: don't know if I am supposed to put m_ for other subsystem variable names. ask later...

  // Commands
  TriggerDrive* pTriggerDrive; //!< Pointer for the TriggerDrive command
  LimitSwitchCommand* liCommand; // just a test for limit switch
  ToggleLight* tglLight; //!< Pointer for the ToggleLight command
  HallEffectTest *heTest;
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

  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  // MyAutoCommand m_myAuto;
  frc::SendableChooser<frc::Command*> m_chooser;
};

#endif //_ROBOT_HG_