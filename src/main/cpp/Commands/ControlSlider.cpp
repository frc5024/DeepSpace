#include "Commands/ControlSlider.h"
#include "Robot.h"

ControlSlider::ControlSlider() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::m_Slider);
  Requires(Robot::m_Piston);
  this->pJoyOp = Robot::m_oi->GetJoystickOperator();
}

// Called just before this Command runs the first time
// aka: every time teleop is enabled
void ControlSlider::Initialize() {
  this->speed    = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void ControlSlider::Execute() {
  // Slide slider
	this->speed = this->pJoyOp->GetX(Hand::kLeftHand);
  Robot::m_Slider->Slide(this->speed);

  if (fabs(this->speed) <= XBOX_DEADZONE_LEFT_JOY)
	{
		this->speed = 0.0;
	}

  // Control piston
  if(this->pJoyOp->GetTriggerAxis(Hand::kRightHand) > 0.8 || this->pJoyOp->GetBumper(Hand::kRightHand)){
    Robot::m_Piston->Deploy();
  } else {
    Robot::m_Piston->Retract();
  }
  
  // Reset the speed
  this->speed = 0.00;

  // Move slider to center if   button is pressed
  if(this->pJoyOp->GetBButton()) {
    Robot::m_Slider->Center();
  } 
}


bool ControlSlider::IsFinished() { return false; }

// Called once after isFinished returns true
void ControlSlider::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlSlider::Interrupted() {}
