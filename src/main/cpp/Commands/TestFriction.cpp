/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/TestFriction.h"
#include "Robot.h"

TestFriction::TestFriction() {
    Requires(Robot::m_DriveTrain);
    this->pGyro = new AHRS(SPI::kMXP);
    this->curSpd = 0.0;
}

void TestFriction::Initialize() {
    this->curSpd = 0.0;
}

void TestFriction::Execute() {
    Robot::m_DriveTrain->ArcadeDrive(curSpd, 0.0);
    this->curSpd += 0.001;
}

bool TestFriction::IsFinished() {
    return this->pGyro->IsMoving();
}

void TestFriction::End() {
    Log("Last known motor speed when static friction broke: "<< this->curSpd);
    Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0);
}

void TestFriction::Interrupted() {
    Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0);
}
