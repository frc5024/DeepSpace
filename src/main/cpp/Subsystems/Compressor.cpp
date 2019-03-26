#include "Subsystems/Compressor.h"
#include <iostream>

cCompressor::cCompressor() : frc::Subsystem("cCompressor") {
  // Initialize the motors
	this->pCompressor = new frc::Compressor(PCM_CAN_ID);
  this->pCompressor->SetClosedLoopControl(false);
}

void cCompressor::InitDefaultCommand() {
  SetDefaultCommand(new ControlCompressor());
}

void cCompressor::SetState(bool enabled){
  std::cout << "Compressor set to: " << enabled << std::endl;
    this->pCompressor->SetClosedLoopControl(enabled);
}