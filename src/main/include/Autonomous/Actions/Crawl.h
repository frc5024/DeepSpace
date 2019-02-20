/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _CRAWL_HG_
#define _CRAWL_HG_

#include <frc/commands/Command.h>

class Crawl : public frc::Command {
public:
	Crawl();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	bool wasOnFloor;
};

#endif /* _CRAWL_HG_ */
