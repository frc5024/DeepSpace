#include "Commands/TriggerDrive.h"
#include "Robot.h"

TriggerDrive::TriggerDrive() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::m_DriveTrain);
  this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
}

// Called just before this Command runs the first time
// aka: every time teleop is enabled
void TriggerDrive::Initialize() {
  // Set speed and direction multipliers
  this->directionMultiplier = 1;
  this->speedMultiplier     = 1;

  //set Speed and Rotation
  this->speed    = 0.0;
  this->rotation = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void TriggerDrive::Execute() {

  // Deal with reversing and slow mode
	this->directionMultiplier *= (this->pJoyDrive->GetXButtonReleased())? -1 : 1;
  this->speedMultiplier      = (this->pJoyDrive->GetBumper(Hand::kRightHand)) ? 0.6 : 1;

  // Get movement data form controller
  // Speed = Right trigger - left trigger
  this->speed = (this->pJoyDrive->GetTriggerAxis(Hand::kRightHand) - this->pJoyDrive->GetTriggerAxis(Hand::kLeftHand));
	this->rotation = this->pJoyDrive->GetX(Hand::kLeftHand);
	
	// Multiply each value with it's multiplier(s)
  this->speed    *= (this->speedMultiplier * this->directionMultiplier);
  this->rotation *= (this->speedMultiplier * DRIVEWITHJOYSTICK_ROTATION_LIMITER);

  Robot::m_DriveTrain->ArcadeDrive(this->speed, this->rotation);
  
  // Reset the speed and rotation
  // while this does have some negitive side effects while driving,
  // It is for saftey. (and so we don't have a run-away bot slam into a wall again)
  this->speed    = 0.00;
  this->rotation = 0.00;
}


bool TriggerDrive::IsFinished() { 
    // Stop if in Auto climb, we still need to drive in kActive mode though
    return (ClimbManager::CurrentClimbState == ClimbManager::ClimbState::kAuto); 
}

// Called once after isFinished returns true
void TriggerDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TriggerDrive::Interrupted() {}
