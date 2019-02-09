#include "Commands/DriveWithJoystick.h"
#include "Robot.h"

DriveWithJoystick::DriveWithJoystick() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::m_DriveTrain);
  this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
}

// Called just before this Command runs the first time
// aka: every time teleop is enabled
void DriveWithJoystick::Initialize() {
  // Set magnitude and direction multipliers
  this->directionMultiplier = 1;
  this->magnitudeMultiplier     = 1;

  //set magnitude and radial
  this->magnitude    = 0.0;
  this->radial = 0.0;
  
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
  // magnitude = Right trigger - left trigger
  this->magnitude = (this->pJoyDrive->GetTriggerAxis(Hand::kRightHand) - this->pJoyDrive->GetTriggerAxis(Hand::kLeftHand));
  
  // needed for use in an and statement
  return true;
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
  // Deal with reversing and slow mode
	this->directionMultiplier = (this->pJoyDrive->GetXButtonReleased())? -1 : 1;
  this->magnitudeMultiplier = (this->pJoyDrive->GetBumper(Hand::kRightHand)) ? 0.5 : 1;

  // Get movement data form controller
  this->magnitude = this->pJoyDrive->GetY(Hand::kLeftHand) * -1;
	this->radial    = this->pJoyDrive->GetX(Hand::kLeftHand);

  // If trigger drive mode was enabled during teleop-init, override magnitude with trigger data
  // This will only ever be called if a select few people are driving the bot.
  // It should be as insignifigant as possible when the bot is in normal operation (3 instructions)
  this->driveMode == 1 && this->getTriggers();
	
	// Multiply each value with it's multiplier(s)
  this->magnitude *= (this->magnitudeMultiplier * this->directionMultiplier);
  this->radial    *= (this->magnitudeMultiplier);// * DRIVEWITHJOYSTICK_ROTATION_LIMITER);

  Robot::m_DriveTrain->ArcadeDrive(this->magnitude, this->radial);
  
  // Reset the magnitude and radial
  // while this does have some negitive side effects while driving,
  // It is for saftey. (and so we don't have a run-away bot slam into a wall again)
  this->magnitude = 0.00;
  this->radial    = 0.00;
}


bool DriveWithJoystick::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveWithJoystick::End() {
  Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted() {
  DriveWithJoystick::End();
}