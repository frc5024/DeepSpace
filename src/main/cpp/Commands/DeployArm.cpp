#include "Commands/DeployArm.h"
#include "Robot.h"

DeployArm::DeployArm(double timeout)
    : TimedCommand(timeout) {
    Requires(Robot::m_Arm);
}

// Called just before this Command runs the first time
void DeployArm::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DeployArm::Execute() {
    Robot::m_Arm->MoveArm(0.2);
}

// Called once after command times out
void DeployArm::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeployArm::Interrupted() {}
