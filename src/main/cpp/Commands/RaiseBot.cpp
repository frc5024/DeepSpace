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
    this->speed =(this->pJoyDrive->GetY(Hand::kLeftHand));

    this->gyro = 0.0; // TODO: set this with gyro roll

    double output = (this->speed-((this->gyro*CLIMB_M)/100)-(1.00-CLIMB_B));

    Robot::m_Arm->MoveArm(output);
    Robot::m_Leg->MoveLeg(this->speed);
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseBot::IsFinished() { 
    if(Robot::m_Arm->getDistanceFromFloor >= CLIMB_MAX_HEIGHT){
        ClimbManager::CurrentClimbState = ClimbManager::ClimbState::kAuto;
        return true; 
    }
    
}

// Called once after isFinished returns true
void RaiseBot::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseBot::Interrupted() {}
