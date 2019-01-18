#include "Commands/PullLeg.h"
#include "Robot.h"

PullLeg::PullLeg() {
    Requires(Robot::m_Leg);
    this->pJoyDrive = Robot::m_oi->GetJoystickOperator();
}

// Called just before this Command runs the first time
void PullLeg::Initialize() {
    //set Speed Multiplyer
    this->speedMultiplier = 1;
    //set Speed
    this->speed = 0.0;
}

//Called repeatedly when this Command is scheduled to run
void PullLeg::Execute() {
    this->speed = (this->speedMultiplier) * (this->pJoyDrive->GetTriggerAxis(Hand::kRightHand));

    Robot::m_Leg->MoveLeg(this->speed);
}

// Make this return true when this Command no longer needs to run execute()
bool PullLeg::IsFinished() { return false; }

// Called once after isFinished returns true
void PullLeg::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PullLeg::Interrupted() {}
