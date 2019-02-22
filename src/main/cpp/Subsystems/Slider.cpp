#include "Subsystems/Slider.h"
#include <iostream>

Slider::Slider() : frc::Subsystem("Slider") {
  // Initialize the motors
	this->pSliderMotor = new can::WPI_TalonSRX(SLIDER_MOTOR);
	this->pSliderMotor->SetInverted(false);
	this->pSliderMotor->SetSafetyEnabled(false);

	this->pLeftHall   = new frc::DigitalInput(3);
	this->pRightHall  = new frc::DigitalInput(0);		
	this->pCenterHall = new frc::DigitalInput(8);	

	/*
	* If sliderSide is 1 it is on the left side.
	* If sliderSide is -1 it is on the right side. 
	*/
	this->sliderSide = 0;

	this->ntTelemetry = NetworkTable::GetTable("SmartDashboard/Telemetry/Slider");
}

void Slider::InitDefaultCommand() {
  SetDefaultCommand(new ControlSlider());
}

void Slider::Slide(double speed) {
	// Make sure the slider is not doing anything bad
	if(speed < 0 && this->pLeftHall->Get()==0) {
		this->pSliderMotor->Set(0);
	}else if(speed > 0 && this->pRightHall->Get()==0) {
		this->pSliderMotor->Set(0);
	}else{
		this->pSliderMotor->Set(speed);
	}
//std::cout << this->pCenterHall->Get() << std::endl;
	if(speed > 0 && this->pCenterHall->Get()==0) {
		this->sliderSide = 1;
	}

	if (speed < 0 && this->pCenterHall->Get()==0) {
		this->sliderSide = -1;		
	}
	
	// Report slider data to NetworkTables 
	this->ntTelemetry->PutBoolean("centre", !this->pCenterHall->Get()); // is centred
	this->ntTelemetry->PutBoolean("left",    this->sliderSide == -1);   // is left
	this->ntTelemetry->PutBoolean("right",   this->sliderSide == 1);    // is right

	return;
}

void Slider::Center() {
	// If the Hall effect is not tripped off, the slider will move to the center
	if(this->pCenterHall->Get()==1) {
		//If the slider are on the right it will move to the left otherwise it will continue right
		if(this->sliderSide==1) {
			this->pSliderMotor->Set(-1);
		} else {
			this->pSliderMotor->Set(1);
		}
	} else {
		this->pSliderMotor->Set(0);
	}
	
	return;
}