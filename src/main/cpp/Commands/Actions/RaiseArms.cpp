#include "Commands/Actions/RaiseArms.h"
#include "Robot.h"

RaiseArms::RaiseArms(double speed, double timeout) : TimedCommand(timeout) {
    Requires(Robot::m_Arm);
    this->speed = speed;
}

// Called just before this Command runs the first time
void RaiseArms::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RaiseArms::Execute() {
    Robot::m_Arm->MoveArm(this->speed);
}

// Called once after command times out
void RaiseArms::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseArms::Interrupted() {}
