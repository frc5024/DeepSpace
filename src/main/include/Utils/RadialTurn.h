/**
 * @file RadialTurn.h
 * @author RaiderRobotics.com
 * @brief Utility class for automatically driving to the grabbed vision target
 * This Object will grab from network tables for the vision target
 * Then calculate a circle to path to the bay perpindicular
 * Then form a trajectory curve along that circle
 * Then follow it until robot reaches target
 * 
 *  ==== HOW TO USE ====
 * 1. Call Start() to grab the vision target distance and angle, program will subsequently calculate the required path
 * 2. Run Execute() as long as it is still turning, program will do PidF to follow along
 * 3. Run Stop() whenever you want, or let the object call Stop() itself when it reaches the target
 * =====================
 * @version 1.0
 * @date 2019-02-06
 */

#ifndef _RADIAL_HG_
#define _RADIAL_HG_

#include <RobotMap.h>
#include <networktables/NetworkTable.h>
#include <iostream>
#include <frc/Timer.h>
#include <Subsystems/DriveTrain.h>

class RadialTurn
{
public:
    /**
     * @brief TODO: documentation
     * 
     */
    void Start(void) ;

    /**
     * @brief TODO: documentation
     * 
     */
    void Execute(void) ;

    /**
     * @brief TODO: documentation
     * 
     */
    void Stop(void) ;

    /**
	 * @brief Construct a new Radial Turn object
	 * @remark Does not need any paramaters but relies on the Vision smartdasboard network table and the drivetrain encoders and navX
	 */
	RadialTurn(void) ;

	/**
	 * @brief Returns the current state of turning the robot is on
	 * State is set to Calculating by Start()
	 * and is then automatically set to the next state by Execute()
	 * @return Returns current state of program use
	 */
	State GetState(void) ;

private:

	/**
	 * @var Angle used to subtract from to grab current angle relative to start of turn
	 * Offset is set when Start() is called
	 */
	float offset ;

	/**
	 * @var Object used to access the NetworkTable(s)
	 * We use this object to access the vision target angle
	 * that is passed to us by the rasPi or whoever's
	 * running the server at the time.
	 */
	std::shared_ptr<NetworkTable> table;

	/**
	 * @var Enum for what state of turning the robot is on
	 * Calculating:		Robot is currently doing time consuming math (WAIT ON IT)
	 * Accelerating:	Robot is currently speeding up to cruise velocity
	 * Cruising:		Robot is currently moving at constant cruise velocity
	 * Deccelerating:	Robot is currently deccelerating to a velocity of 0
	 * Inactive:		Stop() was called, program is not active or running
	 */
	enum State {
		STATE_CALCULATING,
		STATE_ACCELERATING,
		STATE_CRUISING,
		STATE_DECCELERATING,
		STATE_INACTIVE
	} state ;

	/**
	 * @var Storage for the distance in cm of the path for the left side of wheels
	 * That's a long description but hopefully understandable
	 */
	float distancePathSideLeft ;

	/**
	 * @var Storage for the distance in cm of the path for the right side of wheels
	 * That's a long description but hopefully understandable
	 */
	float distancePathSideRight ;

	/**
	 * @var The delta angle in degrees we are turning
	 * Remember to convert radians<->degrees when using
	 */
	float angleTurning ;

	/**
	 * @var Points in time in seconds when the robot switches states
	 * Is set by Start()
	 * Is get by Execute()
	 * 
	 * 0.0 is assumed, it is the the Start() of the program, and is the start of accelerating
	 * timePoint[0] is the the start of the cruising state
	 * timePoint[1] is the start of the deccelerating state
	 * timePoint[2] is the start of the inactive state, otherwise known as the end
	 */
	double timePoint [3] ;

	/**
	 * @brief Timer used to check the timePoints and change states
	 * Gets time in seconds, nothing much else to it
	 * 
	 * Stop reading this, you know what a timer is, you have one on your phone
	 * 
	 * That's it I'm leaving...
	 * @remark Uses system clock, and thus has an accuracy of the system clock
	 */
	frc::Timer* pTimer ;

	/**
	 * @brief Calculates cruise velocity when doing motion profiling
	 * Calculates the maximum obtainable speed,
	 * grabs the maximum velocity constant,
	 * and returns the minimum of the two.
	 * @remark Also uses the constants RADIAL_MAX_VEL and RADIAL_MAX_ACCEL in RobotMap.h
	 * @param initialVelocity	The currenty velocity at the time of calling this
	 * @param distance			The delta distance to travel
	 * @return float 			The absolute cruise velocity in cm/s  for motion profiling
	 */
	float GetCruiseVelocity(float v, float distance) ;

};

#endif /* _RADIALTURN_HG_ */
