/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/TurnFromAngle.h"

TurnFromAngle::TurnFromAngle(void) {
	std::cout << "You must construct TurnFromAngle with a float target angle you dummy, everything will now break...\n" ;
	delete this;
}

TurnFromAngle::TurnFromAngle(float target) {
	std::cout << "TurnFromAngle constructed\n";

	Requires(Robot::m_DriveTrain);
	this->m_pGryo = new AHRS(SPI::Port::kMXP);
	this->m_pTimer = new frc::Timer();

	while (true)
	{
		if (target > 180.0)			target -= 360.0;
		elif (target < -180.0)		target += 360.0;
		else						break;
	}
	std::cout << "Set target to "<< target << " deg\n";
	this->target = target;

	this->pTweak = PID_TWEAK_P / target;
	this->iTweak = PID_TWEAK_I / target;
	// this->dTweak = PID_TWEAK_D / target;
	
	this->integral = 0.0;
}

// Called just before this Command runs the first time
void TurnFromAngle::Initialize() {
	this->m_pGryo->Reset();
	this->m_pTimer->Start();
}

// Called repeatedly when this Command is scheduled to run
void TurnFromAngle::Execute() {
	float current = this->m_pGryo->GetAngle();

	// === CALCULATE PID OUTPUT === 
	this->err = this->target - current;
	this->integral += this->err * CYCLE_TIME;
	// Skip Derivative for now
	// Derr = (err - prevErr) / CYCLE_TIME
	double pid = this->pTweak * this->err + this->iTweak * this->integral; // + this->dTweak * Derr
	if (abs(pid) > 1.0)
		std::cout << "PID output was more than one: ("<<pid<<")\n";
	
	Robot::m_DriveTrain->ArcadeDrive(0, pid);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnFromAngle::IsFinished() {
	if (this->m_pTimer->Get() > PID_TIMEOUT)
		return true;
	if (abs(this->err) < PID_BUFFER)
		return true;
	return false;
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
	Robot::m_DriveTrain->ArcadeDrive(0,0); // Brake
}

AHRS* TurnFromAngle::getGyro(void) {
	return this->m_pGryo;
}
