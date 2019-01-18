#include "Commands/ManageIO.h"
#include "Robot.h"

ManageIO::ManageIO() {
    Requires(Robot::m_Arm);
    this->pJoyDrive = Robot::m_oi->GetJoystickOperator();
}

// Called just before this Command runs the first time
void ManageIO::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ManageIO::Execute() {    
    if(this->pJoyDrive->GetYButtonPressed()) {
        if (Robot::pDeployClimb != nullptr) {
            Robot::pDeployClimb->Start();
        }
    }
}

// Make this return true when this Command no longer needs to run execute()
bool ManageIO::IsFinished() { return false; }

// Called once after isFinished returns true
void ManageIO::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManageIO::Interrupted() {}
