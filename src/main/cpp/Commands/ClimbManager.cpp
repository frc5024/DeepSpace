#include "Commands/ClimbManager.h"
#include "Robot.h"
#include <frc/commands/Scheduler.h>

ClimbManager::ClimbState ClimbManager::CurrentClimbState;

ClimbManager::ClimbManager() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::m_Slider);
	Requires(Robot::m_Flap);
	Requires(Robot::m_HatchGripper);
	Requires(Robot::m_Piston);

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

	// Release all the stuff

	Robot::m_HatchGripper->Retract();
	Robot::m_Flap->Retract();
	Robot::m_Piston->Deploy();
	Robot::m_Slider->Center();

	// Signal all commands to kill themselves
	this->CurrentClimbState = this->ClimbState::kAuto;

	// Start vibrating driver controller
	this->pJoyDrive->SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbManager::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimbManager::End() {
	this->pJoyDrive->SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbManager::Interrupted() {
	this->pJoyDrive->SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.0);
}
