#include "Subsystems/Slider.h"
#include <iostream>
#include "Timer.h"

Slider::Slider() : frc::Subsystem("Slider") {
  // Initialize the motors
	this->pSliderMotor = new can::WPI_TalonSRX(SLIDER_MOTOR);

	this->pLeftHall = new frc::DigitalInput(3);

	this->pRightHall = new frc::DigitalInput(0);		

	this->pCenterHall = new frc::DigitalInput(8);	

	/*
	* If sliderSide is 1 it is on the left side.
	* If sliderSide is -1 it is on the right side. 
	*/
	this->sliderSide = 0;

	this->pSliderMotor->SetInverted(false);

	this->pSliderMotor->SetSafetyEnabled(false);

	this->distence = 0.0;

	this->start = 0.0;
	this->end	= 0.0;
}

void Slider::InitDefaultCommand() {
  SetDefaultCommand(new ControlSlider());
}

void Slider::Slide(double speed) {
	this->pSliderMotor->Set(speed);
	Timer timer;
	if(speed!=0)
	{
		this->start = timer.startTime();
	}
	else
	{
		this->end = timer.elapsed();
		this->distence = sliderSide ? ((end-start)*20.25) : ((end-start)*20.25)*-1;
	}
	
	
	if(speed < 0 && this->pLeftHall->Get()==0) {
		this->pSliderMotor->Set(0);
	}
		
	if(speed > 0 && this->pRightHall->Get()==0) {
		this->pSliderMotor->Set(0);
	}
//std::cout << this->pCenterHall->Get() << std::endl;
	if(speed > 0 && this->pCenterHall->Get()==0) {
		this->sliderSide = 1;
	}

	if (speed < 0 && this->pCenterHall->Get()==0) {
		this->sliderSide = -1;		
	}
	//std::cout << this->sliderSide << std::endl;
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
void Slider::TotalCountedTime()
{
	
}