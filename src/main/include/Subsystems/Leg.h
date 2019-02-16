#ifndef _LEG_HG_
#define _LEG_HG_

#include <frc/commands/Subsystem.h>
#include <frc/DigitalInput.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "RobotMap.h"

class Leg : public frc::Subsystem {

	/**
	 * @brief The last known position of the leg
	 * So we know where we are when we are trying to be somwhere else
	 * @remark Should be updated everytime the leg is moved
	 */
	enum Quadrant
	{
		Q_TOP,
		Q_TOP_MIDDLE,
		Q_MIDDLE,
		Q_MIDDLE_BOTTOM,
		Q_BOTTOM
	} legPosition ;

public:

	/**
	 * @brief Construct a new Leg object
	 */
	Leg(void);

	/**
	 * @brief Who uses this? You dont need to.
	 */
	void InitDefaultCommand() override;

	/**
	 * @brief Move climb leg up or down
	 *
	 * @param Speed range:(-1.00, 1.00) where 1.00 or 100% is upwards
	 */
	void MoveLeg(double Speed);

	/**
	 * @brief Get the last known position
	 * @return Quadrant the quadrant it was last known in
	 */
	Quadrant GetPosition(void) ;

	/**
	 * @brief Returns whether the legs are at the top most position
	 * @return true Sensor is tripped, we are at the top
	 * @return false Sensor is not tripped, we are not at the top
	 */
	bool AtTop(void) ;

	/**
	 * @brief Returns whether the legs are at the middle position
	 * @return true Sensor is tripped, we are at the middle
	 * @return false Sensor is not tripped, we are not at the middle
	 */
	bool AtMiddle(void) ;

	/**
	 * @brief Returns whether the legs are at the bottom most position
	 * @return true Sensor is tripped, we are at the bottom
	 * @return false Sensor is not tripped, we are not at the bottom
	 */
	bool AtBottom(void) ;

private:

	/**
	 * @brief Pointer for the climb leg motor
	 * Works off a winch system to pull up and down
	 * But is used like a talon motor
	 */
	can::WPI_TalonSRX* pLegMotor;

	/**
	 * @brief Sensor for when the leg is as far up as it can go
	 * If this sensor is tripped, the legs are above the wheels
	 * and it is now safe to drive.
	 * @remark When moving the leg up, stop when this gets tripped
	 */
	frc::DigitalInput* pTopHall ;

	/**
	 * @brief Sensor for when the leg is at the middle position
	 * If this sensor is tripped, the robot is above the low raised platform
	 */
	frc::DigitalInput* pMiddleHall ;

	/**
	 * @brief Sensor for when the leg is as far down as it can go
	 * If this sensor is tripped, the robot is above the highest platform
	 * @remark When moving the leg down, stop when this gets tripped
	 */
	frc::DigitalInput* pBottomHall ;

};

#endif // _LEG_HG_