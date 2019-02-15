#include "Commands/Actions/RaiseLegs.h"
#include "Robot.h"

RaiseLegs::RaiseLegs(double speed, double timeout) : TimedCommand(timeout) {
    Requires(Robot::m_Leg);
    this->speed = speed;
}

// Called just before this Command runs the first time
void RaiseLegs::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RaiseLegs::Execute() {
    Robot::m_Leg->MoveLeg(this->speed *-1);
}

// Called once after command times out
void RaiseLegs::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseLegs::Interrupted() {}
