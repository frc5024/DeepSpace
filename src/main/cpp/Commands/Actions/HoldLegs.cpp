#include "Commands/Actions/HoldLegs.h"
#include "Robot.h"

HoldLegs::HoldLegs(double timeout) : TimedCommand(timeout) {
    Requires(Robot::m_Leg);
}

// Called just before this Command runs the first time
void HoldLegs::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HoldLegs::Execute() {
    Robot::m_Leg->MoveLeg(LEG_HOLD_SPEED);
}

// Called once after command times out
void HoldLegs::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HoldLegs::Interrupted() {}
