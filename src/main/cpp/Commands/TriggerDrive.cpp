#include "Commands/TriggerDrive.h"
#include "Robot.h"

TriggerDrive::TriggerDrive() {
    Requires(Robot::m_DriveTrain);
    this->pGyro = new AHRS(SPI::kMXP);
    this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
    this->isReversed = false;
    this->xSpeed = 0.0;
    this->zRotation = 0.0;
    this->xSpeedPrev = 0.0;
    this->zRotationPrev = 0.0;
}

void TriggerDrive::Initialize() {}

void TriggerDrive::Execute() {

    // Check the (X) button, for if the driver wants to reverse directions
    if (this->pJoyDrive->GetXButtonPressed()) this->isReversed = ! this->isReversed;

    // Get whether the right bumper is held or not
    bool isBumperHeld = this->pJoyDrive->GetBumper(Hand::kRightHand);

    // Grab triggers values for x - speed
    this->xSpeed = this->pJoyDrive->GetTriggerAxis(Hand::kRightHand) - this->pJoyDrive->GetTriggerAxis(Hand::kLeftHand);

    // Square the x-speed to create a wide input mapping
    this->xSpeed *= fabs(this->xSpeed);

    // Slow down by 60% if right bumper is held
    if (isBumperHeld) this->xSpeed *= 0.6;

    double xSpeedDelta = this->xSpeed - fabs(this->xSpeedPrev);
    if (xSpeedDelta > MOTOR_OUTPUT_ACCELERATION)
        xSpeedDelta = MOTOR_OUTPUT_ACCELERATION;
    
    // If we're trying to move, but aren't, add a little kick
    if (this->xSpeed >= 0.05)
        if ( ! this->pGyro->IsMoving())
            this->xSpeed += STATIC_FRICTION_MIN_DRIVE_MOTOR_OUTPUT;
    
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

    double zRotationDelta = this->zRotation - this->zRotationPrev;
    if (zRotationDelta > MOTOR_OUTPUT_ROTATION_ACCELERATION) { // Speeding up too fast
        this->zRotation = this->zRotationPrev + MOTOR_OUTPUT_ROTATION_ACCELERATION;
    } else { // Speeding up below limit
        this->zRotation = this->zRotationPrev + zRotationDelta;
    }
    
    // DRIVE! VROOM VROOM!
    Robot::m_DriveTrain->ArcadeDrive(this->xSpeed, this->zRotation);

    // Update past values
    this->xSpeedPrev = this->xSpeed;
    this->zRotationPrev = this->zRotation;
}

bool TriggerDrive::IsFinished() { 
    // Stop the command if we're in auto mode, robot will restart command when out of auto mode
    return ClimbManager::CurrentClimbState == ClimbManager::kAuto;
}

void TriggerDrive::End() {
    Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0);
}

void TriggerDrive::Interrupted() {
    Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0);
}
