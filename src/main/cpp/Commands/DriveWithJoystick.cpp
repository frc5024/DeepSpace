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
  
  // Make sure that driveMode is reset each time the bot is enabled
  // This must be in the Initalize() function, not in the header file
  this->driveMode = 0;

  // If X held during teleop enable, use triggerdrive
  if(this->pJoyDrive->GetYButton()){
  	this->driveMode = 1;
  }
}

bool inline DriveWithJoystick::getTriggers(){
  // Speed = Right trigger - left trigger
  this->speed = (this->pJoyDrive->GetTriggerAxis(XboxController::kRightHand) - this->pJoyDrive->GetTriggerAxis(XboxController::kLeftHand));
  // needed for use in an and statement
  return true;
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
  // Deal with reversing and slow mode
	this->directionMultiplier *= (this->pJoyDrive->GetXButtonReleased())? -1 : 1;
  this->speedMultiplier = (this->pJoyDrive->GetBumper(XboxController::kRightHand)) ? 0.5 : 1;

  // Get movement data form controller
  this->speed    = this->pJoyDrive->GetY(XboxController::kLeftHand) * -1;
	this->rotation = this->pJoyDrive->GetX(XboxController::kLeftHand);

  // An and statement is used. One less instruction to execute in armv7-a.
  // So it is "obviously" better. Right?
  // More faster = more better (or something like that)
  this->driveMode == 1 && this->getTriggers();
	
	// Multiply each value with it's multiplier(s)
  this->speed    *= (this->speedMultiplier * this->directionMultiplier);
  this->rotation *= (this->speedMultiplier * DRIVEWITHJOYSTICK_ROTATION_LIMITER);

  Robot::m_DriveTrain->ArcadeDrive(this->speed, this->rotation);
  this->speed    = 0.00;
  this->rotation = 0.00;
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveWithJoystick::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted() {}
