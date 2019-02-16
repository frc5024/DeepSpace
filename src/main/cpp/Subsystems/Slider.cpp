#include "Subsystems/Slider.h"

Slider::Slider() : frc::Subsystem("Slider") {
  // Initialize the motors
	this->pSliderMotor = new can::WPI_VictorSPX(SLIDER_MOTOR);

	this->pSliderMotor->SetInverted(false);

	this->pSliderMotor->SetSafetyEnabled(false);
}

void Slider::InitDefaultCommand() {
  SetDefaultCommand(new ControlSlider());
}

void Slider::Slide(double speed) {
	this->pSliderMotor->Set(speed);
	return;
}