//< Manual arm override
#include "Commands/PullArm.h"
#include "Robot.h"

PullArm::PullArm() {
    Requires(Robot::m_Arm);
     Requires(Robot::m_CrawlDrive);
    this->pJoyDebug = Robot::m_oi->GetJoystickDebug();
}

// Called just before this Command runs the first time
void PullArm::Initialize() {
    //set Speed Multiplyer
    this->speedMultiplier = 1;
    //set Speed
    this->speed = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void PullArm::Execute() {
    this->speed =(this->pJoyDebug->GetY(Hand::kLeftHand));

    Robot::m_Arm->MoveArm(this->speed);

    Robot::m_CrawlDrive->Move(this->pJoyDebug->GetTriggerAxis(Hand::kRightHand) - this->pJoyDebug->GetTriggerAxis(Hand::kLeftHand));
}

// Make this return true when this Command no longer needs to run execute()
bool PullArm::IsFinished() { 
    return !(ClimbManager::CurrentClimbState == ClimbManager::ClimbState::kInactive); 
}

// Called once after isFinished returns true
void PullArm::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PullArm::Interrupted() {}
