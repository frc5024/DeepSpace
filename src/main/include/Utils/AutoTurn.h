//! Util class for Automatically turning, used in TriggerDrive
#ifndef _AUTOTURN_HG_
#define _AUTOTURN_HG_

#include <iostream>
#include <RobotMap.h>
#include <AHRS.h>
#include <networktables/NetworkTable.h>

/* Lazy mans class, we're basically programming in C now */
namespace AutoTurn {

	/**
	 * @brief Get the angle to the centre of the target and set this target to it
	 * @remark If no vision target is in sight, sets target to 0.0	:)
	 */
	extern void GetData(void) ;

	/**
	 * @brief Called every cycle, actually turns the robot to the target using PID
	 * 
	 * @return double TODO: document
	 */
	extern double Turn(void) ;


	/**
	 * Function for setting the target angle
	 * TODO: document
	 * @param angle Angle to rotate to
	 */
	extern void SetTarget(float angle);

	/**
	 * @brief 
	 * TODO: document
	 */
	extern void Stop(void);

	/**
	 * @var The angle offset of where we want to go
	 */
	extern float target;

	/**
	 * @var Used for PID calculations
	 * This is the integral of the error over time,
	 * Stored becuase it's an integral, it accumalates
	 * @remark Make sure it's reset everytime the target changes
	 */
	extern float integral ;

	/**
	 * @var Pointer to the gyro (navX) which can getAngle, and other cool stuff
	 * This object lets us grab out current angle to do PID calculations
	 */
	extern AHRS* pGyro;

	/**
	 * @var Object used to access the NetworkTable(s)
	 * We use this object to access the vision target angle
	 * that is passed to us by the rasPi or whoever's
	 * running the server at the time.
	 */
	extern std::shared_ptr<NetworkTable> table;



} /* end namespace AutoTurn */

#endif // _AUTOTURN_HG_
