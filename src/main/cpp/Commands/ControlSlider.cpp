#include "Commands/ControlSlider.h"
#include "Robot.h"

/**
 *
 */
ControlSlider::ControlSlider() 
{
  Requires(Robot::m_Slider);
  this->pJoystickOperator = Robot::m_oi->GetJoystickOperator();
}

/**
 *
 */
void ControlSlider::Initialize() 
{
  this->speed = 0.0;
	
  return;
}

/**
 *
 */
void ControlSlider::Execute() 
{
  this->speed = this->pJoystickOperator->GetX(Hand::kLeftHand);
  Robot::m_Slider->Slide(this->speed);
	
  return;
}

/**
 *
 */
bool ControlSlider::IsFinished() 
{ 
  return false; 
}

/**
 *
 */
void ControlSlider::End() 
{
  Robot::m_Slider->Slide(0.0);
}

/**
 *
 */
void ControlSlider::Interrupted() 
{
  Robot::m_Slider->Slide(0.0);
}
