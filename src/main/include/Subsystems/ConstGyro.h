/**
 * @file	ConstGyro.h
 * @author	RaiderRobotics.com
 * @brief	Subsystem for the gyro, allows the creation of multiple angle getters
 * @version	0.1
 * @date	2019-02-27
 *     ----==== HOW TO USE ====----
 * 1. Call CreateAngleGetter() and store the returned byte,
 *    this creates an offset to zero the yaw when this is called,
 *    and returns an id for you to use in step 2
 * 2. Call GetAngle(byte), passing in the id you stored from step 1.
 *    Do this as much as you want, but not whenever (not thread safe)
 * 3. Call DeleteAngleGetter() when you're done
 *    Please don't forget this step and failsafe delete it 
 */
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _CONSTGYRO_HG_
#define _CONSTGYRO_HG_

#include <frc/commands/Subsystem.h>
#include <AHRS.h>

#define ARRAY_SZ	4

class ConstGyro : public frc::Subsystem {
private:

	/**
	 * @var Gyro object, don't touch
	 * Pointer to the gyro, this is the object for the gyro, this is the gyro
	 * If you touch it, you pay for it!
	 */
	AHRS* pGyro;

	/**
	 * @var Array of angle offsets, used for GetAngle(byte)
	 * Change ARRAY_SZ to change the number of available offsets at once
	 * @remark Size is pre-defined as ARRAY_SZ
	 */
	float* offsets;

public:

	/**
	 * @brief Constructor the for the class
	 * @remark Constructs a new navX gyro plugged into the RIO directly
	 * Default, void, and only constructor. A NavX is excpected to exist
	 * in the port on the RIO the NavX directly plugs in to.
	 */
	ConstGyro(void);

	/**
	 * @brief Returns pointer to this gyro
	 * @remrk Please do not use unless for testing and debugging reasons
	 * @return AHRS* This gyro, the one you're using, the only one on the robot
	 */
	AHRS* GetGyro(void);

	/**
	 * @brief Sets up Angle getter with the returned id
	 *    ----==== HOW TO USE ====----
	 * 1. Call CreateAngleGetter() and store the returned byte,
	 *    this creates an offset to zero the yaw when this is called,
	 *    and returns an id for you to use in step 2
	 * 2. Call GetAngle(byte), passing in the id you stored from step 1.
	 *    Do this as much as you want, not whenever (not thread safe)
	 * 3. Call DeleteAngleGetter() when you're done
	 *    Please don't forget this step and failsafe delete it 
	 * @return int8_t The id to be passed to GetAngle, store this for as long as you need it, is nullptr on error(non available)
	 * @return int8_t -1 on failure: (mem full)
	 */
	int8_t CreateAngleGetter(void);

	/**
	 * @brief Releases an angle offset at the given
	 * ----==== HOW TO USE ====----
	 * 1. Call CreateAngleGetter() and store the returned byte,
	 *    this creates an offset to zero the yaw when this is called,
	 *    and returns an id for you to use in step 2
	 * 2. Call GetAngle(byte), passing in the id you stored from step 1.
	 *    Do this as much as you want, not whenever (not thread safe)
	 * 3. Call DeleteAngleGetter() when you're done
	 *    Please don't forget this step and failsafe delete it 
	 * @param id The id for the offset to release
	 */
	void DeleteAngleGetter(int8_t id);

	/**
	 * @brief Getter for the yaw of the robot, relative to game start
	 * Simply directly calls the gyro's GetYaw.
	 * @remark Angle returned is continuous, meaning angle can surpass 360deg and so on
	 * @remark Angle is zeroed such that 0deg is forward face from red alliance and 180 deg is froward face from blue alliance
	 * @return float Accumulated yaw angle degrees. 0 is front face red alliance or about face on blue alliance
	 */
	float GetAngle(void);
	
	/**
	 * @brief Get the Angle object
	 *    ----==== HOW TO USE ====----
	 * 1. Call CreateAngleGetter() and store the returned byte,
	 *    this creates an offset to zero the yaw when this is called,
	 *    and returns an id for you to use in step 2
	 * 2. Call GetAngle(byte), passing in the id you stored from step 1.
	 *    Do this as much as you want, not whenever (not thread safe)
	 * 3. Call DeleteAngleGetter() when you're done
	 *    Please don't forget this step and failsafe delete it
	 * @param id The id for the gette you created
	 * @return float The accumulated yaw degrees angle
	 * @return float 0.0 on failure (out-of-bounds id)
	 */
	float GetAngle(int8_t id);

	/**
	 * @brief Getter for the yaw of the robot, relative to game start
	 * Simply directlty calls the gyro's GetYaw.
	 * @remark Angle returned is not continuous
	 * @return float Yaw angle degrees relative to game start, R:(-180, 180)
	 */
	float GetYaw(void);

	/**
	 * @brief Getter for the pitch of the robot, relative to game start
	 * Simply directly calls the gyro's GetPitch.
	 * @return float Pitch angle degrees relative to game start
	 */
	float GetPitch(void);

	/**
	 * @brief Getter for the roll of the robot, relative to game start
	 * Simply directly calls the gyro's GetRoll.
	 * @return float Roll angle degrees
	 */
	float GetRoll(void);

	/**
	 * @brief Useless
	 * Who uses this?
	 */
	void InitDefaultCommand() override;
};

#endif /* _CONSTGYRO_HG_ */
