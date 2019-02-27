/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/ConstGyro.h"

ConstGyro::ConstGyro() : Subsystem("Gyro") {
	this->pGyro = new AHRS(SPI::Port::kMXP);
	this->offsets = new float[ARRAY_SZ];
}

void ConstGyro::InitDefaultCommand() {}

AHRS* ConstGyro::GetGyro(void) {
	return this->pGyro;
}

int8_t ConstGyro::CreateAngleGetter(void) {
	for (uint8_t i = 0 ; i < ARRAY_SZ ; i++) {
		if (this->offsets[i] == 0.0) {
			this->offsets[i] = this->GetAngle();
			return i ;
		}
	}
	return -1 ;
}

void ConstGyro::DeleteAngleGetter(int8_t id) {
	if (id < 0 || id > ARRAY_SZ) return ;
	this->offsets[id] = 0.0 ;
}

float ConstGyro::GetAngle(void) {
	return this->pGyro->GetAngle();
}

float ConstGyro::GetAngle(int8_t id) {
	if (id < 0 || id > ARRAY_SZ) return 0.0 ;
	return this->GetAngle() - this->offsets[id] ;
}

float ConstGyro::GetYaw(void) {
	return this->pGyro->GetYaw();
}

float ConstGyro::GetPitch(void) {
	return this->pGyro->GetPitch();
}

float ConstGyro::GetRoll(void) {
	this->pGyro->GetRoll();
}
