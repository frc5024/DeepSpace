#include "Commands/ControlCargo.h"
#include "Robot.h"

ControlCargo::ControlCargo() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::m_Cargo);
  this->pJoyOp = Robot::m_oi->GetJoystickOperator();
}

// Called just before this Command runs the first time
void ControlCargo::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ControlCargo::Execute() {
  if(this->pJoyOp->GetTriggerAxis(Hand::kLeftHand) > 0.8){
    Robot::m_Cargo->Deploy();
  }else{
    Robot::m_Cargo->Retract();
  }
}

// Make this return true when this Command no longer needs to run execute()
bool ControlCargo::IsFinished() { return false; }

// Called once after isFinished returns true
void ControlCargo::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlCargo::Interrupted() {}
