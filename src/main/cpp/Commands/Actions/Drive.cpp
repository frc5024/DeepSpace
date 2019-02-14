#include "Commands/Actions/Drive.h"
#include "Robot.h"

Drive::Drive(double speed, double timeout) : TimedCommand(timeout) {
    Requires(Robot::m_DriveTrain);
    this->speed = speed;
}

// Called just before this Command runs the first time
void Drive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
    Robot::m_DriveTrain->ArcadeDrive(this->speed, 0.0);
}

// Called once after command times out
void Drive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {}
