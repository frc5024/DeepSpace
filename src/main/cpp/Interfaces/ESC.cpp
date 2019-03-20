#include <Interfaces/ESC.h>

// // TalonSRX
// void ESC::TalonSRX::InitEncodingMode(){
//     this->ConfigFactoryDefault();
//     this->SetSensorPhase(true);
// }
// void ESC::TalonSRX::InitEncodingMode(bool phase){
//     this->ConfigFactoryDefault();
//     this->SetSensorPhase(phase);
// }

// int ESC::TalonSRX::GetPosition() {
//     return this->GetSensorCollection().GetPulseWidthPosition();
// }

ESC::TalonSRX::TalonSRX(int port) : frc::SpeedController(port){
    
}