#include "Commands/TriggerDrive.h"
#include "Robot.h"

TriggerDrive::TriggerDrive() {
    Requires(Robot::m_DriveTrain);
    this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
    this->isReversed = false;
    this->xSpeed = 0.0;
    this->zRotation = 0.0;
}

void TriggerDrive::Initialize() {
    // Don't reset isReversed, as ClimbMode resets this command
    this->xSpeed = 0.0;
    this->zRotation = 0.0;
}

void TriggerDrive::Execute() {

    // Get whether the right bumper is held or not
    bool isBumperHeld = this->pJoyDrive->GetBumper(Hand::kRightHand);

    // Grab triggers values for x - speed
    this->xSpeed = this->pJoyDrive->GetTriggerAxis(Hand::kRightHand) - this->pJoyDrive->GetTriggerAxis(Hand::kLeftHand);

    // Square the x-speed to create a wide input mapping
    this->xSpeed *= fabs(this->xSpeed);

    // Slow down by 60% if right bumper is held
    if (isBumperHeld) this->xSpeed *= 0.6;

    // Check the (X) button, for if the driver wants to reverse directions
    if (this->pJoyDrive->GetXButtonPressed()) this->isReversed;

    // Check reverse direction
    if (this->isReversed) this->xSpeed = - this->xSpeed;

    // Grab x-joystick value for z rotation
    this->zRotation = this->pJoyDrive->GetX(Hand::kLeftHand);

    // Square the z-rotation to create a wide input mapping
    this->zRotation *= fabs(this->zRotation);

    // Lessen the turn rate for easier control
    this->zRotation *= DRIVEWITHJOYSTICK_ROTATION_LIMITER;

    // Slow down rotation if right bumper is held
    if (isBumperHeld) this->zRotation *= 0.7;

    Robot::m_DriveTrain->ArcadeDrive(this->xSpeed, this->zRotation);

    Robot::m_Dr

}


bool TriggerDrive::IsFinished() { 
  return !(ClimbManager::CurrentClimbState == ClimbManager::ClimbState::kInactive); 
}

// Called once after isFinished returns true
void TriggerDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TriggerDrive::Interrupted() {}
