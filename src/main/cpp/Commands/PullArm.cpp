//< Manual arm override
#include "Commands/PullArm.h"
#include "Robot.h"
#include <iostream>

// Arms and legs
// speed controlled by trigger, and arm output controled by equation (networktables input?)

PullArm::PullArm() {
    Requires(Robot::m_Arm);
     Requires(Robot::m_CrawlDrive);
    this->pJoyDebug = Robot::m_oi->GetJoystickDebug();

    this->sd = NetworkTable::GetTable("SmartDashboard");
}

// Called just before this Command runs the first time
void PullArm::Initialize() {
    //set Speed Multiplyer
    this->speedMultiplier = 1;
    //set Speed
    this->speed = 0.0;

    this->gyro = 0.0;

    // Climb settings
    // TODO: move these to ROBOTMAP.h
    this->m = 0.6;
    this->b = 0.65;
}

// Called repeatedly when this Command is scheduled to run
void PullArm::Execute() {
    this->speed =(this->pJoyDebug->GetY(Hand::kRightHand)*-1);

    if (fabs(this->speed) < 0.1){
        this->speed = 0.0;
        return;
    }

    this->gyro = Robot::m_Arm->GetAngle();
    std::cout << this->gyro << std::endl;

    // double output = (this->speed-(((this->gyro*this->m)*-1)/1000)-(1.00-this->b));
    double output = ((this->speed) * this->b);

    Robot::m_Arm->MoveArm(output); 

    Robot::m_CrawlDrive->Move(this->pJoyDebug->GetTriggerAxis(Hand::kRightHand) - this->pJoyDebug->GetTriggerAxis(Hand::kLeftHand));

    // this->sd->PutNumber("Arm_Output", output);
}

// Make this return true when this Command no longer needs to run execute()
bool PullArm::IsFinished() { return false; }

// Called once after isFinished returns true
void PullArm::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PullArm::Interrupted() {}