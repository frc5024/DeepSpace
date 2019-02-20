/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _LOWERARM_HG_
#define _LOWERARM_HG_

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class LowerArm : public frc::Command {
public:
	LowerArm(float speed, float timeout);
	void Initialize()	override;
	void Execute()		override;
	bool IsFinished()	override;
	void End()			override;
	void Interrupted()	override;
private:
	float speed; //!< Whole-percent power to use for arm
	float timeout; //!< Maximum time to run command for in seconds. The 'timeout' time.
	frc::Timer* pTimer; //!< Timer for timeing out the command
};

#endif /* _LOWERARM_HG_ */
