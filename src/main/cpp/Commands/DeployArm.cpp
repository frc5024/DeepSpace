#include "Commands/DeployArm.h"
#include "Robot.h"

DeployArm::DeployArm(double timeout, double speed) : TimedCommand(timeout) {
    // Use Requires() here to declare subsystem dependencies
    Requires(Robot::m_Arm);
    this->speed = speed;
}

// Called just before this Command runs the first time
void DeployArm::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DeployArm::Execute() {
    // Moves the Arm
    Robot::m_Arm->MoveArm(this->speed);
}

// Called once after command times out
void DeployArm::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeployArm::Interrupted() {}
