#include "Commands/ControlLight.h"
#include "Robot.h"

ControlLight::ControlLight() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::m_Light);
  this->pJoyOp = Robot::m_oi->GetJoystickOperator();
}

// Called just before this Command runs the first time
// aka: every time teleop is enabled
void ControlLight::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ControlLight::Execute() {
  if(this->pJoyOp->GetXButtonPressed()){
      if(this->state==true) {
        Robot::m_Light->Off();
        this->state = false;
      } else {
        Robot::m_Light->On();
        this->state = true;
      }
    }
}


bool ControlLight::IsFinished() { return false; }

// Called once after isFinished returns true
void ControlLight::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlLight::Interrupted() {}
