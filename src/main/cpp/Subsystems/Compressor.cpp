#include "Subsystems/Compressor.h"
#include <iostream>

Compressor::Compressor() : frc::Subsystem("Compressor") {
  // Initialize the motors
	this->pCompressor = new frc::Compressor(PCM_CAN_ID);
}

void Compressor::InitDefaultCommand() {
  SetDefaultCommand(new ControlCompressor());
}

void Compressor::SetState(bool enabled){
  std::cout << "Compressor set to: " << enabled << std::endl;
    this->pCompressor->SetClosedLoopControl(enabled);
}