#include "Commands/Actions/HoldArms.h"
#include "Robot.h"

HoldArms::HoldArms(double timeout) : TimedCommand(timeout) {
    Requires(Robot::m_Arm);
}

// Called just before this Command runs the first time
void HoldArms::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HoldArms::Execute() {
    Robot::m_Arm->MoveArm(ARM_HOLD_SPEED);
}

// Called once after command times out
void HoldArms::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HoldArms::Interrupted() {}
