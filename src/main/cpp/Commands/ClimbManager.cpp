#include "Commands/ClimbManager.h"
#include "Robot.h"
#include <frc/commands/Scheduler.h>

ClimbManager::ClimbState ClimbManager::CurrentClimbState;

ClimbManager::ClimbManager() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
  this->pJoyOp    = Robot::m_oi->GetJoystickOperator();

  this->CurrentClimbState = this->ClimbState::kInactive;
}

// Called just before this Command runs the first time
void ClimbManager::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimbManager::Execute() {
  if (!(this->pJoyDrive->GetBumper(Hand::kLeftHand) && this->pJoyOp->GetAButton() && this->pJoyOp->GetBButton())){
    return;
  }

  // Signal all commands to kill themselves
  this->CurrentClimbState = this->ClimbState::kSemiAuto;

  // Start vibrating driver controller
  this->pJoyDrive->SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbManager::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimbManager::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbManager::Interrupted() {}
