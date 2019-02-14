#include "Commands/ClimbManager.h"
#include "Robot.h"
#include <frc/commands/Scheduler.h>

ClimbManager::ClimbManager() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
  this->pJoyOp    = Robot::m_oi->GetJoystickOperator();
}

// Called just before this Command runs the first time
void ClimbManager::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimbManager::Execute() {
  if (!(this->pJoyDrive->GetBumper(Hand::kLeftHand) && this->pJoyOp->GetAButton() && this->pJoyOp->GetBButton())){
    return;
  }

  // Robot::CancelTeleop();
  frc::Scheduler::GetInstance();
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbManager::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimbManager::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbManager::Interrupted() {}
