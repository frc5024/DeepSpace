/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/TurnAngle.h"
#include <Robot.h>

TurnAngle::TurnAngle() {
  std::cout << "TurnAngle constructed\n";

	Requires(Robot::m_DriveTrain);
	this->m_pGryo = new AHRS(SPI::Port::kMXP);
	this->m_pTimer = new frc::Timer();

	this->target = 0.0 ;
  
	// Get that driver controller
	this->pJoyDrive = Robot::m_oi->GetJoystickDrive();

	// Get that network table
	this->table = NetworkTable::GetTable("SmartDashboard/Vision");
	
	return ;
}

// Called just before this Command runs the first time
void TurnAngle::Initialize() {
	std::cout << "TurnAngle initializing\n" ;
}

void TurnAngle::SetTarget(float angle) {
	while (true) {
		if (angle > 180.0)		angle -= 360.0;
		elif (angle < -180.0)	angle += 360.0;
		else					break;
	} 
	this->target = angle ;
	std::cout << "Set target to ("<<target<<")\n" ;

	return ;
}

void TurnAngle::Go(void) {
	this->m_pTimer->Reset() ;
	this->m_pGryo->Reset() ;

	float angle = this->table->GetNumber("Motor", 0.0);
	this->SetTarget(angle) ;

	this->m_pTimer->Start() ;

	return ;
}

void TurnAngle::Stop(void) {
	Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0) ;
	this->target = 0.0 ;
	this->m_pGryo->Reset() ;
	this->m_pTimer->Reset() ;
	this->m_pTimer->Stop() ;

	return ;
}

void TurnAngle::Turn(void) {
	float current = this->m_pGryo->GetAngle() ;
	float err = this->target - current ;

	if (fabs(err) < 1) {
		this->Stop() ;
		return ;
	}
	if (this->m_pTimer->Get() > 5) {
		this->Stop() ;
		return ;
	}

	if (err > 0.0) {
		std::cout << "Turning right...\n" ;
		Robot::m_DriveTrain->ArcadeDrive(0.0, 0.5) ;
	} else {
		std::cout << "Turning left...\n" ;
		Robot::m_DriveTrain->ArcadeDrive(0.0, -0.5) ;
	}
	
	return ;
}

// Called repeatedly when this Command is scheduled to run
void TurnAngle::Execute() {
	
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
	if (this->pJoyDrive->GetAButton())
		this->Turn() ;

	return ;
}

// Make this return true when this Command no longer needs to run execute()
bool TurnAngle::IsFinished() { return false; }

// Called once after isFinished returns true
void TurnAngle::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnAngle::Interrupted() {
	std::cout << "TurnAngle was interrupted\n" ;
}
