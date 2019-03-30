/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"

namespace rr{
  class PIDController {
  public:
    PIDController(double kp, double ki, double kd);
    double Feed(double input, double current);

  private:
    double kp, ki, kd;
    double p, i, d;
    double error, output, prevError;
    double lastOutput;
  };
}