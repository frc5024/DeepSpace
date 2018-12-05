#include "Commands/DriveWithJoystick.h"

#include "Robot.h"

DriveWithJoystick::DriveWithJoystick() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::m_DriveTrain);
  this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
}

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize() {
  // Set speed and direction multipliers
  this->directionMultiplier = 1;
  this->speedMultiplier     = 1;

  //set Speed and Rotation
  this->speed    = 0.0;
  this->rotation = 0.0;
  
  //driverMenu selection
  //To use driverMenu, hold a selection button while enabling teleop
  
  // If X held, use triggerdrive
  if(this->pJoyDrive->GetYButton()){
  	this->driveMode = 1;
  }
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
  // Deal with reversing and slow mode
	this->directionMultiplier *= (this->pJoyDrive->GetXButtonReleased())? -1 : 1;
  this->speedMultiplier = (this->pJoyDrive->GetBumper(XboxController::kRightHand)) ? 0.5 : 1;

  // Get movement data form controller
  this->speed    = this->pJoyDrive->GetY(XboxController::kLeftHand) * -1;
	this->rotation = this->pJoyDrive->GetX(XboxController::kLeftHand);


  if(this->driveMode == 1){
  	// speed = right trigger - left trigger
	  this->speed = (this->pJoyDrive->GetTriggerAxis(XboxController::kRightHand) - this->pJoyDrive->GetTriggerAxis(XboxController::kLeftHand));
  }

  this->speed    = (this->speed    * this->speedMultiplier * this->directionMultiplier);
  this->rotation = (this->rotation * this->speedMultiplier);

  Robot::m_DriveTrain->ArcadeDrive(this->speed, this->rotation * 0.8);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveWithJoystick::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted() {}
