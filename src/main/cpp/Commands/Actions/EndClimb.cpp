#include "Commands/Actions/EndClimb.h"
#include "Robot.h"

EndClimb::EndClimb(double timeout) : TimedCommand(timeout) {
    this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
}

// Called just before this Command runs the first time
void EndClimb::Initialize() {
    ClimbManager::CurrentClimbState = ClimbManager::ClimbState::kInactive;
    this->pJoyDrive->SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0);
}

// Called repeatedly when this Command is scheduled to run
void EndClimb::Execute() {}

// Called once after command times out
void EndClimb::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EndClimb::Interrupted() {}
