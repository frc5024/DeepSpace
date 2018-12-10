/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _INTAKE_HG_
#define _INTAKE_HG_

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <DoubleSolenoid.h>
#include <ctre/Phoenix.h>
#include <RobotMap.h>

class Intake : public frc::Subsystem {
public:
	Intake() ;
	void InitDefaultCommand() override ;
	void IntakeUse(double spd) ; ///< \param	spd		Positive number intakes, negative number spits out
	void OpenGripper(void) ;
	void CloseGripper(void) ;
	bool IsGripperClosed(void) ; ///< Returns true if closed, false if open

private:
	can::WPI_TalonSRX* pLeftMotor ; ///< Slave
	can::WPI_TalonSRX* pRightMotor ; ///< Master
	frc::DoubleSolenoid* pGripperSolenoid;
	bool gripperClosed ;
} ;

#endif // _INTAKE_HG_
