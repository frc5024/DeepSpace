/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _RAISEBOTHIGH_HG_
#define _RAISEBOTHIGH_HG_

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class RaiseBotHigh : public frc::Command {
public:
	RaiseBotHigh(void);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	frc::Timer* pTimer; //!< Timer to timeout the command if sensors fail
	bool  onFloor ; //!< Is robot currently on the floor?
};

#endif /* _RAISEBOTHIGH_HG_ */
