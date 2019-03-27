/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _AUTOCLIMBHIGH_HG_
#define _AUTOCLIMBHIGH_HG_

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class AutoClimbHigh : public frc::Command {
public:
	AutoClimbHigh();
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

    bool IsClimbing() ;
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

    bool climbing ;
};

#endif /* _AUTOCLIMBHIGH_HG_ */
