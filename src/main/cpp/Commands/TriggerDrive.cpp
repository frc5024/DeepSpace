#include "Commands/TriggerDrive.h"
#include "Robot.h"

TriggerDrive::TriggerDrive() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::m_DriveTrain);
	this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
	this->pTurnFromAngle = new TurnFromAngle() ;
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
	
	// Vision table
  this->table = NetworkTable::GetTable("SmartDashboard/Vision");
}

// Called repeatedly when this Command is scheduled to run
void TriggerDrive::Execute() {
	// Deal with reversing and slow mode
	this->directionMultiplier = (this->pJoyDrive->GetXButtonReleased())? -1 : 1;
	this->speedMultiplier     = (this->pJoyDrive->GetBumper(Hand::kRightHand)) ? 0.5 : 1;

	// Get movement data form controller
	// Speed = Right trigger - left trigger
	this->speed = (this->pJoyDrive->GetTriggerAxis(Hand::kRightHand) - this->pJoyDrive->GetTriggerAxis(Hand::kLeftHand));
	this->rotation = this->pJoyDrive->GetX(Hand::kLeftHand);

	// Multiply each value with it's multiplier(s)
	this->speed    *= (this->speedMultiplier * this->directionMultiplier);
	this->rotation *= (this->speedMultiplier * DRIVEWITHJOYSTICK_ROTATION_LIMITER);

	// if A button, override movement with vision input
	if (this->pJoyDrive->GetAButtonPressed()) {
		std::cout << "A button pressed!\n" ;
		float angle = this->table->GetNumber("Motor", 0.0) ;
		std::cout << "Turning to angle ("<<angle<<")\n" ;
		this->pTurnFromAngle->Reset() ;
		this->pTurnFromAngle->SetTarget(angle) ;
		this->pTurnFromAngle->Start() ;
	}
	elif (this->pJoyDrive->GetAButtonReleased()) {
		std::cout << "A button released!\n" ;
		if (this->pTurnFromAngle->IsRunning()) {
			std::cout << "Cancelling command.\n" ;
			this->pTurnFromAngle->Cancel() ;
		}
	}


	Robot::m_DriveTrain->ArcadeDrive(this->speed, this->rotation);

	// Reset the speed and rotation
	// while this does have some negitive side effects while driving,
	// It is for saftey. (and so we don't have a run-away bot slam into a wall again)
	this->speed    = 0.00;
	this->rotation = 0.00;
	}


bool TriggerDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void TriggerDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TriggerDrive::Interrupted() {}
