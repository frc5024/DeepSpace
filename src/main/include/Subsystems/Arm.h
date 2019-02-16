//! A subsystem that controls the Arm of the robot
#ifndef _ARM_HG_
#define _ARM_HG_

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <frc/Spark.h>
#include <frc/AnalogInput.h>
#include <frc/PWMVictorSPX.h>
#include <ctre/Phoenix.h>
#include "RobotMap.h"
#include <frc/DigitalInput.h>

class Arm : public frc::Subsystem {
public:
	Arm();
	void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (Arm)

	/**
	 * Move Arm arm up or down
	 *
	 * @param Speed speed (from -1 to 1)
	 */
	void MoveArm(double Speed);


	/**
	 * returns distance from floor
	 *
	 */
	double getDistanceFromFloor();

	
	bool GetSensor(void) ;

private:
	can::WPI_TalonSRX* pArmMotor; //!< Pointer for Arm arm motor
	can::WPI_TalonSRX* pArmMotor2; //!< Pointer for Arm arm motor

	frc::DigitalInput* pArmHall ; //!< hall effects for arm is lowered enough


	frc::AnalogInput m_ultrasonic{CLIMB_ULTRASONIC};
	frc::DigitalInput* pDeployLimit;
	static constexpr double kValueToInches = 0.125;
};

#endif // _ARM_HG_