#include "iostream"
#include "Commands/ToggleLight.h"
#include <Robot.h>

ToggleLight::ToggleLight() {
  Requires(Robot::m_DriveTrain);
  this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
}

// Called just before this Command runs the first time
void ToggleLight::Initialize() {
  this->relayState = false;
  this->lightRelay->Set(frc::Relay::Value::kOff);
 // this->exampleSolenoid.Set(false);
}

// Called repeatedly when this Command is scheduled to run
void ToggleLight::Execute() {
  if (this->pJoyDrive->GetBButtonReleased())
  {
    // Used for testing:
    std::cout << "B button pressed! Light toggleed" << std::endl;
    
    relayState = !relayState;

    if (relayState)
    {
      //this->lightRelay->Set(frc::Relay::Value::kOn);  
      //this->exampleSolenoid.Set(true);
    }
    else
    {
      //this->lightRelay->Set(frc::Relay::Value::kOff);
      //this->exampleSolenoid.Set(false);
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
