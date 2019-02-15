//< Manual arm override
#include "Commands/RaiseBot.h"
#include "Robot.h"

RaiseBot::RaiseBot() {
    Requires(Robot::m_Arm);
     Requires(Robot::m_CrawlDrive);
    this->pJoyDrive = Robot::m_oi->GetJoystickDebug();
}

// Called just before this Command runs the first time
void RaiseBot::Initialize() {
    // Set speed
    this->speed = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void RaiseBot::Execute() {
    this->speed =(this->pJoyDrive->GetY(Hand::kLeftHand) * -1);

    double output = (this->speed*0.63);

    Robot::m_Arm->MoveArm(output);
    Robot::m_Leg->MoveLeg(this->speed * -1);
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseBot::IsFinished() { 
    if(Robot::m_Arm->getDistanceFromFloor() >= CLIMB_MAX_HEIGHT){
        ClimbManager::CurrentClimbState = ClimbManager::ClimbState::kAuto;
        return true; 
    }
    return false;
    
}

// Called once after isFinished returns true
void RaiseBot::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseBot::Interrupted() {}
