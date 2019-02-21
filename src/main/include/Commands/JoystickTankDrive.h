/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _JOYSTICKTANKDRIVE_HG_
#define _JOYSTICKTANKDRIVE_HG_

#include <frc/commands/Command.h>
#include <frc/XboxController.h>

class JoystickTankDrive : public frc::Command {
public:
	JoystickTankDrive();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	frc::XboxController* pJoyDrive ; //!< Pointer to driver's controller
	bool isReverse ;
};

#endif /* _JOYSTICKTANKDRIVE_HG_ */
