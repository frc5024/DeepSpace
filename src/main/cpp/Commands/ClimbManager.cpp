#include "Commands/ClimbManager.h"
#include "Robot.h"
#include <iostream>
#include <frc/commands/Scheduler.h>

ClimbManager::ClimbState ClimbManager::CurrentClimbState;

ClimbManager::ClimbManager() {
	this->pJoyOp = Robot::m_oi->GetJoystickOperator();

	this->CurrentClimbState = this->ClimbState::kInactive;
}

// Called just before this Command runs the first time
void ClimbManager::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimbManager::Execute() {
    if (!( (this->pJoyOp->GetPOV() == 90) &&  (this->pJoyOp->GetTriggerAxis(Hand::kLeftHand) > 0.8)))
    {
        return;
	}
    
    // Signal all commands to kill themselves
    this->CurrentClimbState = this->ClimbState::kActive;

	// Start vibrating driver controller
	this->pJoyOp->SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbManager::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimbManager::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbManager::Interrupted() {
}