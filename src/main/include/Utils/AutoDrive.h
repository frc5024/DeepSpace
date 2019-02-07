/**
 * @file AutoDrive.h
 * @author RaiderRobotics.com
 * @brief Utility class for automatically driving to the grabbed vision target
 * This Object will grab from network tables for the vision target
 * Then calculate a circle to path to the bay perpindicular
 * Then form a trajectory curve along that circle
 * Then follow it until robot reaches target
 * 
 *  ==== HOW TO USE ====
 * 1. Call Start() to grab the vision target distance and angle, program will subsequently calculate the required path
 * 2. Run Execute() as long as it is still turning, program will do PIDF to follow along
 * 3. Run Stop() whenever you want, or let the object call Stop() itself when it reaches the target
 * =====================
 * @version 1.0
 * @date 2019-02-06
 */

#ifndef _AUTODRIVE_HG_
#define _AUTODRIVE_HG_

#include <RobotMap.h>
#include 
#include <Subsystems/DriveTrain.h>

class AutoDrive
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
	 * @brief Construct a new Auto Drive object
	 * Does not need any paramaters but relies on the Vision smartdasboard network table and the drivetrain encoders
	 */
	AutoDrive(void) ;

	/**
	 * @brief Returns whether the robot is currently turning
	 * Is true if Start() was called last or false if Stop() was called last
	 * @return Returns whether the robot is doing turning calculations/output
	 */
	bool IsTurning(void) ;

private:

	/**
	 * @var Angle used to subtract from to grab current angle in relavence to start of turn
	 * Offset is set when Start() is called
	 */
	float offset ;

	/**
	 * @var The angle to the target, relevent to the robot
     * Used to determine path, stored just in case, don't actually NEED to
	 */
	float target ;

	/**
	 * @var Keeps track of whether robot is in the middle of turning or not
	 * (The A button can be held but the robot will not turn as it has reached its target)
	 * @remark Use IsTurning() to Get this variable
	 */
	bool turning ;

	/**
	 * @var Used for PID calculations
	 * This is the integral of the error over time,
	 * Stored becuase it's an integral, it accumalates
	 * @remark Is reset when Start() is called
	 */
	float integral ;

	/**
	 * @var Object used to access the NetworkTable(s)
	 * We use this object to access the vision target angle
	 * that is passed to us by the rasPi or whoever's
	 * running the server at the time.
	 */
	std::shared_ptr<NetworkTable> table;

};

#endif /* _AUTODRIVE_HG_ */
