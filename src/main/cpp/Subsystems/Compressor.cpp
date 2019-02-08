#include "Subsystems/Compressor.h"

Compressor::Compressor() : frc::Subsystem("Compressor") {
  // Initialize the motors
	this->pCompressor = new frc::Compressor();
}

void Compressor::InitDefaultCommand() {
  SetDefaultCommand(new ControlCompressor());
}

void Compressor::SetState(bool enabled){
    this->pCompressor->SetClosedLoopControl(enabled);
}