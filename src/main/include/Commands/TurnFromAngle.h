/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Command.h>
#include <Subsystems/DriveTrain.h>
#include <Robot.h>
#include <iostream>
#include <RobotMap.h>
#include <AHRS.h>
#include <Timer.h>

class TurnFromAngle : public frc::Command {
public:
	TurnFromAngle(); ///< Dont use this one
	TurnFromAngle(float target) ; ///< Use this one
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	AHRS* getGyro(void);

private:
	float pTweak;
	float iTweak;
	// float TWEAK_D; // Not using
	float target; //< Target angle in degrees
	float err; //< Target angle in degrees minus current angle in degrees
	float integral; //< Integral of current angle in degrees per sec
	AHRS* m_pGryo;
	frc::Timer* m_pTimer;

};
