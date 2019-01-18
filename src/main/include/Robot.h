//! Main robot class that is called by wpilib
#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/TimedRobot.h>
#include <cameraserver/CameraServer.h>

#include "Commands/TriggerDrive.h"
#include "Commands/testUltra.h"
#include "Commands/PullArm.h"
#include "Commands/PullLeg.h"
#include "Commands/DeployClimb.h"
#include "Commands/ManageIO.h"
#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/CrawlDrive.h"
#include "Subsystems/Arm.h"
#include "Subsystems/Leg.h"


class Robot : public frc::TimedRobot {
 public:
	// Subsystems
  static DriveTrain *m_DriveTrain; //!< Pointer for the DriveTrain
  static CrawlDrive *m_CrawlDrive; //!< Pointer for the DriveTrain
  static Arm *m_Arm;               //!< Pointer for the Arm
  static Leg *m_Leg;               //!< Pointer for the Leg
  static OI *m_oi;                 //!< Pointer for the Operator Interface (OI)

	// Commands
  TriggerDrive* pTriggerDrive; //!< Pointer for the TriggerDrive command
  testUltra* pTestUltra;
  PullArm* pPullArm;
  PullLeg* pPullLeg;
  DeployClimb* pDeployClimb;
  ManageIO* pManageIO;
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
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  // MyAutoCommand m_myAuto;
  frc::SendableChooser<frc::Command*> m_chooser;
};

#endif //_ROBOT_HG_