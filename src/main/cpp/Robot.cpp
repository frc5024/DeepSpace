#include "Robot.h"
#include "Utilities/Log.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

#include "Autonomous/CommandGroups/CGCenterFrontLeft.h"
#include "Autonomous/CommandGroups/CGCenterFrontRight.h"
#include "Autonomous/CommandGroups/CGJustDriveForward.h"
#include "Autonomous/CommandGroups/CGLowerLeftBack.h"
#include "Autonomous/CommandGroups/CGLowerLeftMiddle.h"
#include "Autonomous/CommandGroups/CGLowerLeftFront.h"
#include "Autonomous/CommandGroups/CGLowerRightBack.h"
#include "Autonomous/CommandGroups/CGLowerRightMiddle.h"
#include "Autonomous/CommandGroups/CGLowerRightFront.h"
#include "Autonomous/CommandGroups/CGUpperLeftBack.h"
#include "Autonomous/CommandGroups/CGUpperLeftMiddle.h"
#include "Autonomous/CommandGroups/CGUpperLeftFront.h"
#include "Autonomous/CommandGroups/CGUpperRightBack.h"
#include "Autonomous/CommandGroups/CGUpperRightMiddle.h"
#include "Autonomous/CommandGroups/CGUpperRightFront.h"
#include "Autonomous/Commands/CMDJustDriveForwardTimed.h"

// Subsystems
DriveTrain *Robot::m_DriveTrain;
OI *Robot::m_oi;

void Robot::RobotInit() {
  // Print out a banner to the shell
  // Some backslashes are doubled in order for them to print properly
  std::cout << "   Welcome 5024!" << std::endl;
  std::cout << "-------------------" << std::endl;
  std::cout << "Robot Starting.."<< std::endl;

  // Subsystems
  this->m_DriveTrain = new DriveTrain();
  this->m_oi = new OI();

  // Init camera
  std::cout << "Starting CameraServer.." << std::endl;
  this->frontCam = frc::CameraServer::GetInstance()->StartAutomaticCapture("Front Cam", CAMERASERVER_FRONT_CAMERA);
  this->backCam  = frc::CameraServer::GetInstance()->StartAutomaticCapture("Back Cam",  CAMERASERVER_BACK_CAMERA);
	
	// Init commands
  std::cout << "Creating Commands.." << std::endl;
  this->pTriggerDrive = new TriggerDrive();

  // Set robot loop speed (in seconds)
  std::cout << "Setting Period Time.." << std::endl;
  // this->SetPeriod(0.01);

  // AUTONOMOUS SETUP
	// setup robot positions
	scRobotPosition.SetDefaultOption("1. Upper Left" , RobotPosition::UPPER_LEFT);
	scRobotPosition.AddOption       ("2. Lower Left" , RobotPosition::LOWER_LEFT);
	scRobotPosition.AddOption       ("3. Centre"     , RobotPosition::CENTER);
	scRobotPosition.AddOption       ("4. Upper Right", RobotPosition::UPPER_RIGHT);
	scRobotPosition.AddOption       ("5. Lower Right", RobotPosition::LOWER_RIGHT);
	frc::SmartDashboard::PutData    ("Robot Position", &scRobotPosition);

	// setup hatch positions
	scHatchPosition.SetDefaultOption("1. Back"       , HatchPosition::BACK);
	scHatchPosition.AddOption       ("2. Middle"     , HatchPosition::MIDDLE);
	scHatchPosition.AddOption       ("3. Front"      , HatchPosition::FRONT);
	frc::SmartDashboard::PutData    ("Hatch Position", &scHatchPosition);

	// setup autonomous type
	scAutonomousType.SetDefaultOption("1. Driver Controlled", AutonomousType::DRIVE_CONTROLLED);
	scAutonomousType.AddOption       ("2. Timed Just Drive Forward", AutonomousType::TIMED_JUST_DRIVE_FORWARD);
	scAutonomousType.AddOption       ("3. Motion Profile Just Drive Forward", AutonomousType::MOTION_PROFILE_JUST_DRIVE_FORWARD);
	scAutonomousType.AddOption       ("4. Total Autonomous", AutonomousType::TOTAL_AUTONOMOUS);
	frc::SmartDashboard::PutData     ("Hatch Position", &scAutonomousType);
}

/**
 *
 */
void Robot::RobotPeriodic() {}

/**
 *
 */
void Robot::DisabledInit() {}

/**
 *
 */
void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 *
 */
void Robot::AutonomousInit()
{
	LOG("[Robot] Autonomous Initialized");

	int autoType = GetAutoType();
  pAutonomousCommand = nullptr;

	LOG("[Robot] Auto Type: " << autoType);

  if (autoType < 200)                                      // Driver controlled so nothing to do
  {
  } 
  else if (autoType < 300)                                 // Timed just drive forward
  {
    pAutonomousCommand = new CMDJustDriveForwardTimed();
  } else if (autoType < 400)                               // Motion profile just drive forward
  {
    pAutonomousCommand = new CGJustDriveForward();
  }
  else if (autoType < 500)                                 // Total Autonomous
  {
    
    if (autoType > 430)         // Back hatch
    {
      switch (scRobotPosition.GetSelected())
      {
        case RobotPosition::UPPER_LEFT : pAutonomousCommand = new CGUpperLeftBack  (); break;
        case RobotPosition::LOWER_LEFT : pAutonomousCommand = new CGLowerLeftBack  (); break;
        case RobotPosition::CENTER     : pAutonomousCommand = new CGCenterFrontLeft(); break;
        case RobotPosition::UPPER_RIGHT: pAutonomousCommand = new CGUpperRightBack (); break;
        case RobotPosition::LOWER_RIGHT: pAutonomousCommand = new CGLowerRightBack (); break;
      }
    } 
    else if (autoType > 420) // Middle hatch
    {
      switch (scRobotPosition.GetSelected())
      {
        case RobotPosition::UPPER_LEFT : pAutonomousCommand = new CGUpperLeftMiddle (); break;
        case RobotPosition::LOWER_LEFT : pAutonomousCommand = new CGLowerLeftMiddle (); break;
        case RobotPosition::CENTER     : pAutonomousCommand = new CGCenterFrontLeft (); break;
        case RobotPosition::UPPER_RIGHT: pAutonomousCommand = new CGUpperRightMiddle(); break;
        case RobotPosition::LOWER_RIGHT: pAutonomousCommand = new CGLowerRightMiddle(); break;
      }
    } 
    else if (autoType > 410) // Front hatch
    {
       switch (scRobotPosition.GetSelected())
      {
        case RobotPosition::UPPER_LEFT : pAutonomousCommand = new CGUpperLeftFront  (); break;
        case RobotPosition::LOWER_LEFT : pAutonomousCommand = new CGLowerLeftFront  (); break;
        case RobotPosition::CENTER     : pAutonomousCommand = new CGCenterFrontRight(); break;
        case RobotPosition::UPPER_RIGHT: pAutonomousCommand = new CGUpperRightFront (); break;
        case RobotPosition::LOWER_RIGHT: pAutonomousCommand = new CGLowerRightFront (); break;
      }
    }
  }

	if (pAutonomousCommand != nullptr) 
  {
	  LOG("[Robot] Starting autonomous");
    pAutonomousCommand->Start();
  } 
  else 
  {
	  LOG("[Robot] No autonomous");
  }

	return;
}

/**
 *
 */

void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 *
 */
void Robot::TeleopInit()
{
	// Stop any Autonomous Command
	if (this->pAutonomousCommand != nullptr)
	{
		this->pAutonomousCommand->Cancel();
		this->pAutonomousCommand = nullptr;
	}

  if (this->pTriggerDrive != nullptr) 
  {
		this->pTriggerDrive->Start();
	}
}

/**
 *
 */
void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 *
 */
void Robot::TestPeriodic() {}


/**
 * Return sum of sendable chooser options so we can decide where we need to go
 */
int Robot::GetAutoType()
{
	int _RP = scRobotPosition.GetSelected();
	int _HP = scHatchPosition.GetSelected();
	int _AT = scAutonomousType.GetSelected();

	LOG("[Robot] Robot Position: " << _RP << " - Hatch Position: " << _HP << " - Auto Type: " << _AT);

	return _RP + _HP + _AT;
}

/**
 *
 */
#ifndef RUNNING_FRC_TESTS
int main(){
  // Start the robot
  WinGame(Robot);
  return 1;
}
#endif