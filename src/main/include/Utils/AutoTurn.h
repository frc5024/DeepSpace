/**
 * @file AutoTurn.h
 * @author RaiderRobotics.com
 * @version 1.0
 * @date 2019-01-31
 * @brief Util class for Automatically turning, used in TriggerDrive
 * Class does not inherit frc::Command,
 * instead an instance of AutoTurn exists in TriggerDrive to be used
 * 
 *===== HOW TO USE =============-----------
 * 1. Call Start() to grab vision target and target angle
 * 2. Call Execute() EVERY CYCLE, which returns the calculated zRotation value output 
 * 3. Stop() will automatically be called when it has reached the target
 * 
 * a. this->turning will be true until Stop() is called, check against this
 * b. You are safe to call Stop() yourself whenever
 * c. As mentioned it is critical you call Execute() every ROBOT_CYCLE_TIME
 *==============================-----------
 */

#ifndef _AUTOTURN_HG_
#define _AUTOTURN_HG_

#include <iostream>
#include <RobotMap.h>
#include <AHRS.h>
#include <networktables/NetworkTable.h>

class AutoTurn {
public:

	/**
	 * @brief Get the angle to the centre of the target and set this target to it
	 * @remark If no vision target is in sight, sets target to 0.0	:)
	 */
	void Start(void) ;

	/**
	 * @brief Called every cycle, actually turns the robot to the target using PID
	 * @remark It is important this function is consistently called as it relies on ROBOT_CYCLE_TIME intervals
	 * @return Returns the motor output for this moment
	 */
	double Execute(void) ;

	/**
	 * @brief Called when the robot has reached the target
	 * Function will reset stored values to 0
	 */
	void Stop(void);

	/**
	 * @brief Construct a new Auto Turn object
	 * Does not need any paramaters but relies on the Vision smartdasboard network table and the navX gyro
	 */
	AutoTurn(void);

	/**
	 * @brief Returns whether the robot is currently turning
	 * Is true if Start() was called last or false if Stop() was called last
	 * @return Returns whether the robot is doing turning calculations/output
	 */
	bool IsTurning(void);

private:

	/**
	 * @var Angle used to subtract from to grab current angle in relavence to start of turn
	 * Offset is set when Start() is called
	 */
	float offset;

	/**
	 * @var The angle offset of where we want to go
	 */
	float target;

	/**
	 * @var Keeps track of whether robot is in the middle of turning or not
	 * The A button can be held but the robot will not turn as it has reached its target
	 * get() this var to check wheter it's turning or not
	 */
	bool turning;

	/**
	 * @var Used for PID calculations
	 * This is the integral of the error over time,
	 * Stored becuase it's an integral, it accumalates
	 * @remark Make sure it's reset everytime the target changes
	 */
	float integral ;

	/**
	 * @var Pointer to the gyro (navX) which can getAngle, and other cool stuff
	 * This object lets us grab out current angle to do PID calculations
	 */
	AHRS* pGyro;

	/**
	 * @var Object used to access the NetworkTable(s)
	 * We use this object to access the vision target angle
	 * that is passed to us by the rasPi or whoever's
	 * running the server at the time.
	 */
	std::shared_ptr<NetworkTable> table;

};

#endif // _AUTOTURN_HG_
