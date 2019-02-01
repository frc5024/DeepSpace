#include "Commands/TriggerDrive.h"
#include "Robot.h"

TriggerDrive::TriggerDrive() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::m_DriveTrain);
	this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
	this->m_pAutoTurn = new AutoTurn() ;
}

// Called just before this Command runs the first time
// aka: every time teleop is enabled
void TriggerDrive::Initialize() {
	// Set speed and direction multipliers
	this->directionMultiplier = 1;
	this->speedMultiplier     = 1;

	//set Speed and Rotation
	this->speed    = 0.0;
	this->rotation = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void TriggerDrive::Execute() {
	// l with reversing and slow mode
	this->directionMultiplier *= (this->pJoyDrive->GetXButtonReleased())? -1 : 1;
	this->speedMultiplier      = (this->pJoyDrive->GetBumper(Hand::kRightHand)) ? 0.6 : 1;

	// Get movement data form controller
	// Speed = Right trigger - left trigger
	this->speed = (this->pJoyDrive->GetTriggerAxis(Hand::kRightHand) - this->pJoyDrive->GetTriggerAxis(Hand::kLeftHand));
	this->rotation = this->pJoyDrive->GetX(Hand::kLeftHand);

	// Multiply each value with it's multiplier(s)
	this->speed    *= (this->speedMultiplier * this->directionMultiplier);
	this->rotation *= (this->speedMultiplier * DRIVEWITHJOYSTICK_ROTATION_LIMITER);

	// If the A button is pressed
	if (this->pJoyDrive->GetAButtonPressed()) {

		// Start auto turning
		this->m_pAutoTurn->Start() ;
	}
	// If the A button is being held
	if (this->pJoyDrive->GetAButton()) {

		// Take over zRotation, calculate AutoTurn PID
		this->rotation = this->m_pAutoTurn->Execute() ;
	} else
	// If the A button is released
	if (this->pJoyDrive->GetAButtonReleased()) {
		
		// Stop auto turning
		this->m_pAutoTurn->Stop() ;
	}

	Robot::m_DriveTrain->ArcadeDrive(this->speed, this->rotation);

}

bool TriggerDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void TriggerDrive::End() {

	// Brakes, so that we don't have a runaway robot
	Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0) ;

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TriggerDrive::Interrupted() {

	// Brakes, so that we don't have a runaway robot
	Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0) ;
	
}
