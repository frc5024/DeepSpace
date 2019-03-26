//! A subsystem that controls the Arm of the robot
#ifndef _ARM_HG_
#define _ARM_HG_

#include <iostream>
#include <frc/commands/Subsystem.h>
#include <frc/DigitalInput.h>
#include <frc/WPILib.h>
#include <frc/Spark.h>
#include <frc/AnalogInput.h>
#include <frc/PWMVictorSPX.h>
#include <ctre/Phoenix.h>
#include "RobotMap.h"

class Arm : public frc::Subsystem {
public:
	Arm();
	void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (Arm)

	/**
	 * @brief Move Arm arm up or down
	 *
	 * @param Speed speed (from -1 to 1), where 1 is forward-down
	 */
	void MoveArm(double Speed);

	/**
	 * @brief Returns whether the hall effects is tripped
	 * This is the sensor for when the arm is lowered
	 * @return true The arm is fully lowered, the sensor is tripped
	 * @return false Sensor is not tripped
	 */
	bool GetSensor(void) ;

private:
	can::WPI_TalonSRX* pArmMotor; //!< Pointer for Arm arm motor
	can::WPI_TalonSRX* pArmMotor2; //!< Pointer for Arm arm motor

	frc::DigitalInput* pArmHall ; //!< hall effects for arm is lowered enough
};

#endif // _ARM_HG_