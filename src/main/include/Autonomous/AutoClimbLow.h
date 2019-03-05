/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _AUTOCLIMBLOW_HG_
#define _AUTOCLIMBLOW_HG_

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class AutoClimbLow : public frc::Command {
public:
	AutoClimbLow();
	void Initialize() override;
	void Execute() override; //!< Switch checks the stage and then calls the appropriate Execute_<Stage>() function
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	void Execute_LowerArm(void);	//!< Execute stage LOWER_ARM stuff
	void Execute_LowerLeg(void);	//!< Execute stage LOWER_LEG stuff
	void Execute_Crawl(void);		//!< Execute stage CRAWL stuff
	void Execute_Drive(void);		//!< Execute stage DRIVE stuff
	void Execute_Raiseleg(void);	//!< Execute stage RAISE_LEG stuff
private:
	/**
	 * @brief Enum for tracking which stage of climb the robot is on
	 * The stage is changed in the Execute_<Stage>() functions
	 */
	enum Stage : uint8_t {
		S_LOWER_ARM,
		S_LOWER_LEG,
		S_CRAWL,
		S_DRIVE,
		S_RAISE_LEG,
		S_FINISHED
	} stage ;

	frc::Timer* pTimer;

	bool onFloor ;

};

#endif /* _AUTOCLIMBLOW_HG_ */
