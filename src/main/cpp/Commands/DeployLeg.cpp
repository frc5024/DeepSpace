#include "Commands/DeployLeg.h"
#include "Robot.h"

DeployLeg::DeployLeg(double timeout)
    : TimedCommand(timeout) {
    Requires(Robot::m_Leg);
}

// Called just before this Command runs the first time
void DeployLeg::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DeployLeg::Execute() {
    Robot::m_Leg->MoveLeg(0.2);
}

// Called once after command times out
void DeployLeg::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeployLeg::Interrupted() {}
