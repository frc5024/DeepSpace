/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _TESTFRICTION_HG_
#define _TESTFRICTION_HG_

#include <frc/commands/Command.h>
#include <AHRS.h>
#include <iostream>

class TestFriction : public frc::Command {
public:
    TestFriction();
    void Initialize()   override;
    void Execute()      override;
    bool IsFinished()   override;
    void End()          override;
    void Interrupted()  override;
private:
    AHRS* pGyro; //!< Pointer for the gyro
    double curSpd; //!< Current speed to drive at
};

#endif /* _TESTFRICTION_HG_ */
