/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Autonomous/AutoHighClimb.h"

AutoHighClimb::AutoHighClimb()
{
	/* Lowers arm to platform	*
	 * before going full power	*/
	AddSequential(new LowerArm(0.4, 0.5)) ;

	/* Pull front of robot up	*
	 * above the platform		*/
	AddSequential(new LowerArm(1.0, 6.0)) ;

	/* Bring back of robot up	*
	 * to be level, to drive	*/
	AddSequential(new LowerLeg()) ;

	/* Crawl forward until we	*
	 * are on the platform		*/
	AddSequential(new Crawl()) ;

	/* Consists of 3 stages controlled		*
	 * by the passage of time...			*
	 * 1: Bring arms up and drive forward	*
	 * 2: Stop the arms and drivetrain		*
	 *	  and bring the legs up				*/
	AddSequential(new FinishClimb()) ;

	std::cout << "Successfully finished climbing... Yay!\n";

}
