#include "Commands/ToggleLight.h"
#include <Robot.h>

ToggleLight::ToggleLight() {
  Requires(Robot::m_DriveTrain);
  this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
}

// Called just before this Command runs the first time
void ToggleLight::Initialize() {
  this->lightRelay->Set(frc::Relay::Value::kOff);
}

// Called repeatedly when this Command is scheduled to run
void ToggleLight::Execute() {
  if (this->pJoyDrive->GetBButtonReleased())
  {
    relayState = !relayState;

    if (relayState)
    {
      this->lightRelay->Set(frc::Relay::Value::kOn);  
    }
    else
    {
      this->lightRelay->Set(frc::Relay::Value::kOff);
    }
  }

}

// Make this return true when this Command no longer needs to run execute()
bool ToggleLight::IsFinished() { return false; }

// Called once after isFinished returns true
void ToggleLight::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleLight::Interrupted() {}
