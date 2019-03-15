#include "Commands/Climb.h"
#include "Robot.h"

Climb::Climb() {
    Requires(Robot::m_Arm);
    Requires(Robot::m_Leg);
    Requires(Robot::m_CrawlDrive);
    this->pJoyOp = Robot::m_oi->GetJoystickOperator();
}

// Called just before this Command runs the first time
void Climb::Initialize() {
    this->armSpeed = 0.0;
    this->crawlSpeed = 0.0;
    this->legSpeed = 0.0;
} 

// Called repeatedly when this Command is scheduled to run
void Climb::Execute() {
    // Move arms
    this->armSpeed = this->pJoyOp->GetY(Hand::kRightHand) * -1;

    // Set crawl speed
    this->crawlSpeed = (this->pJoyOp->GetPOV() == 0)   ? 1  : 0;
    this->crawlSpeed = (this->pJoyOp->GetPOV() == 180) ? -1 : this->crawlSpeed;

    // Set leg speed
    this->legSpeed = this->pJoyOp->GetBumper(Hand::kRightHand)? -1 : 0; 
    this->legSpeed = this->pJoyOp->GetBumper(Hand::kLeftHand) ?  1 : this->legSpeed; 

    if(this->legSpeed < 0.0){
        Utils::EdgeLight::Append(LedColour::kSOLID_GREEN);
    }

    // Set motor outputs
    Robot::m_Arm->MoveArm(this->armSpeed);
    Robot::m_CrawlDrive->Move(this->crawlSpeed);
    Robot::m_Leg->MoveLeg(this->legSpeed);

    // Reset speeds
    this->armSpeed   = 0.0;
    this->crawlSpeed = 0.0;
    this->legSpeed   = 0.0;
}

// Make this return true when this Command no longer needs to run execute()
bool Climb::IsFinished() { return false; }

// Called once after isFinished returns true
void Climb::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Climb::Interrupted() {}
