/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _LOWERLEG_HG_
#define _LOWERLEG_HG_

#include <frc/commands/Command.h>

class LowerLeg : public frc::Command {
public:
	LowerLeg();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
  void Interrupted() override;
};

#endif /* _LOWERLEG_HG_ */
