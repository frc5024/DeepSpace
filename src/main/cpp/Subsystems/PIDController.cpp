/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/PIDController.h"

rr::PIDController::PIDController(double kp, double ki, double kd) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->output = 0.0;
    this->prevError = 0.0;
}

double rr::PIDController::Feed(double input, double current){
    this->error = input - current;
    this->i += (error * ROBOT_PERIOD);
    this->d = (error - this->prevError) / ROBOT_PERIOD;
    this->output = (this->kp * this->error) + (this->ki * this->i) + (this->kd * this->d);
    this->prevError = this->error;
    std::cout << "IN: " << input << " err: " << this->error << " i: " << this->i << " d: " << this->d << " out: " << this->output << std::endl;
    return this->output;
}