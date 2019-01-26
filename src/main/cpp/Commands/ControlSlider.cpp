#include "Commands/ControlSlider.h"
#include "Robot.h"

ControlSlider::ControlSlider() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::m_Slider);
  this->pJoyDrive = Robot::m_oi->GetJoystickOperator();
}

// Called just before this Command runs the first time
// aka: every time teleop is enabled
void ControlSlider::Initialize() {
  this->speed    = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void ControlSlider::Execute() {
	this->speed = this->pJoyDrive->GetX(Hand::kLeftHand);
	
  Robot::m_Slider->slide(this->speed);
  
  // Reset the speed
  this->speed    = 0.00;
}


bool ControlSlider::IsFinished() { return false; }

// Called once after isFinished returns true
void ControlSlider::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlSlider::Interrupted() {}
