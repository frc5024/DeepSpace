/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Autonomous/AutoHighClimb.h"

AutoHighClimb::AutoHighClimb()
{
	/* Lowers arm to platform by	 *
	 * moving the armm at half speed *
	 * for a tenth of a second		 */
	AddSequential(new LowerArm()) ;

	/* Does the following . . .				*
	 * A Brings arms down and stops when	*
	 *    the hall effects is tripped		*
	 * B. Brings legs down and stops when	*
	 *    the hall effects is tripped		*
	 * C. Crawls forward until optical		*
	 *    sensor detects we are on the		*
	 *    ground and were in the air.		*
	 * ! Command stops when C passes !		*/
	AddSequential(new RaiseBotHigh()) ;

	/* Consists of 3 stages controlled		*
	 * by the passage of time...			*
	 * 1: Bring arms up and drive forward	*
	 * 2: Stop the arms, keep driving		*
	 * 3: Stop driving, bring legs up		*/
	AddSequential(new FinishClimb()) ;

}
