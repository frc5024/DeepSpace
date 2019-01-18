/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/TurnFromAngle.h"
#include "Robot.h"

TurnFromAngle::TurnFromAngle(void) {
	std::cout << "TurnFromAngle constructed\n";

	Requires(Robot::m_DriveTrain);
	this->m_pGryo = new AHRS(SPI::Port::kMXP);
	this->m_pTimer = new frc::Timer();

	this->target = 0.0 ;

	this->pTweak = 0.0 ;
	this->iTweak = 0.0 ;
	// this->dTweak = PID_TWEAK_D / target;

	// Get that driver controller
	this->pJoyDrive = Robot::m_oi->GetJoystickDrive();

	// Get that network table
	this->table = NetworkTable::GetTable("SmartDashboard/Vision");
	
	this->integral = 0.0;

	return ;
}

TurnFromAngle::TurnFromAngle(float angle) {
	Requires(Robot::m_DriveTrain);

	std::cout << "Constructed TurnFromAngle with angle ("<<angle<<")\n" ;
	
	this->m_pGryo = new AHRS(SPI::Port::kMXP);
	this->m_pTimer = new frc::Timer() ;
	// this->dTweak = PID_TWEAK_D / target;
	
	this->integral = 0.0;

	this->SetTarget(angle) ;

	return ;
}

void TurnFromAngle::SetTarget(float angle) {
	if (angle == 0.0) {
		std::cout << "attempted to set target to 0.0, not doing that\n" ;
		return ;
	}
/*	while (true) {
		if (angle > 180.0)		angle -= 360.0;
		elif (angle < -180.0)	angle += 360.0;
		else					break;
	} */
	this->target = angle ;
	this->pTweak = PID_TWEAK_P / target ;
	this->iTweak = PID_TWEAK_I / target ;
	//this->dTweak = PID_TWEAK_D / target ; // not in use
	std::cout << "target: " << angle << " deg\n";
	std::cout << "pTweak: " << this->pTweak << " = " << PID_TWEAK_P << " / " << target << "\n" ;
	std::cout << "iTweak: " << this->iTweak << " = " << PID_TWEAK_I << " / " << target << "\n" ;

	return ;
}

void TurnFromAngle::Reset(void) {
	this->err = 0.0 ;
	this->integral = 0.0 ;
	this->target = 1.0 ;
	this->pTweak = 0.0 ;
	this->iTweak = 0.0 ;
	this->m_pTimer->Reset() ;
	this->m_pGryo->Reset() ;
	
	return ;
}

// Called just before this Command runs the first time
void TurnFromAngle::Initialize() {
	std::cout << "TurnFromAngle starting...2\n" ;
	this->m_pGryo->Reset();
}

void TurnFromAngle::Go(void) {
	//	float angle = this->table->GetNumber("Motor", 0.0) ;
		float angle = 90.0 ;
	std::cout << "Turning to angle ("<<angle<<")\n" ;
	this->Reset() ;
	this->SetTarget(angle) ;
	this->m_pTimer->Start();

	return ;
}
void TurnFromAngle::Stop(void) {
	Robot::m_DriveTrain->ArcadeDrive(0,0); // Brake
	this->m_pTimer->Stop() ;
	this->Reset() ;

	return ;
}

float TurnFromAngle::CalculatePID(void) {

	// Grab values
	float current = this->m_pGryo->GetAngle();
	this->err = this->target - current;
	this->integral += this->err * CYCLE_TIME;

	double pid = this->pTweak * this->err + this->iTweak * this->integral; // + this->dTweak * Derr
	
	std::cout << "\""<<pid<<" = "<<this->pTweak<<" * "<<this->err<<" + "<<this->iTweak<<" * "<<this->integral<<"\"\n" ;
	
	return pid ;
}

bool TurnFromAngle::CheckFinished(void) {
	// Check if we've been going for too long
	if (this->m_pTimer->Get() > PID_TIMEOUT) {
		std::cout << "Timed out\n" ;
		return true ;
	}
	if (fabs(this->err) < PID_BUFFER) {
		std::cout << "Reached target\n" ;
		return true ;
	}

	return false ;
}

// Called repeatedly when this Command is scheduled to run
void TurnFromAngle::Execute() {

	if (this->pJoyDrive->GetAButtonPressed()) {
		std::cout << "A button pressed!\n" ;
		this->Go() ;
	}
	else if (this->pJoyDrive->GetAButtonReleased()) {
		std::cout << "A button released!\n" ;
		this->Stop() ;
		return ;
	}

	// turn from angle if a button is held
	if (this->pJoyDrive->GetAButton()) {

		// Do math
		float output = this->CalculatePID() ;

		// Are we done yet
		if (this->CheckFinished()) {
			this->Stop() ;
			return ;
		}

		// DRIVE
		Robot::m_DriveTrain->ArcadeDrive(0, output);

		return ;
	}
	
}

// Make this return true when this Command no longer needs to run execute()
bool TurnFromAngle::IsFinished() {
	
}

// Called once after isFinished returns true
void TurnFromAngle::End() {
	Robot::m_DriveTrain->ArcadeDrive(0,0); // Brake
	this->m_pTimer->Reset();
	this->m_pGryo->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnFromAngle::Interrupted() {
	std::cout << "TurnFromAngle was interrupted and will now End\n" ;
	Robot::m_DriveTrain->ArcadeDrive(0,0); // Brake

	return ;
}

AHRS* TurnFromAngle::GetGyro(void) {
	return this->m_pGryo;
}
