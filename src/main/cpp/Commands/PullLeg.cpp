//< Manual leg override
#include "Commands/PullLeg.h"
#include "Commands/ClimbManager.h"
#include "Robot.h"

PullLeg::PullLeg() {
    Requires(Robot::m_Leg);
    this->pJoyDebug = Robot::m_oi->GetJoystickDebug();
}

// Called just before this Command runs the first time
void PullLeg::Initialize() {
    //set Speed
    this->speed = 0.0;
}

//Called repeatedly when this Command is scheduled to run
void PullLeg::Execute() {
    this->speed = this->pJoyDebug->GetY(Hand::kRightHand);

    Robot::m_Leg->MoveLeg(this->speed);
}

// Make this return true when this Command no longer needs to run execute()
bool PullLeg::IsFinished() { return ClimbManager::CurrentClimbState == ClimbManager::ClimbState::kActive; }

// Called once after isFinished returns true
void PullLeg::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PullLeg::Interrupted() {}
