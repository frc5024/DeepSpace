#include <rrlib/Components/Encoder.h>

/* EncodingDevice */
rr::components::EncodingDevice::EncodingDevice(double circumferenceCM){
    this->circumference = circumferenceCM;
}

int rr::components::EncodingDevice::GetTicks(){
    return 0;
}

double rr::components::EncodingDevice::GetCM(){
    return (this->GetTicks() / this->tpr) * this->circumference;
}

double rr::components::EncodingDevice::GetInch(){
    return (((this->GetTicks() / this->tpr) * this->circumference) * 2.54);
}

double rr::components::EncodingDevice::GetRevs(){
    return (this->GetTicks() / this->tpr);
}

void rr::components::EncodingDevice::Reset(){
    this->tickOffset = this->GetTicks();
}

/* TalonAdapter */
rr::components::TalonAdapter::TalonAdapter(can::WPI_TalonSRX *talon, double circumferenceCM, int ticksPerRev, bool invert) : EncodingDevice(circumferenceCM){
    this->talon = talon;
    this->tpr = ticksPerRev;
    this->talon->ConfigFactoryDefault();
    this->talon->SetSensorPhase(true);
    this->talon->SetSelectedSensorPosition(0, 0, 10);
    this->invert = (invert) ? -1.0 : 1.0;
}

int rr::components::TalonAdapter::GetTicks(){
    return ((this->talon->GetSelectedSensorPosition() * this->invert) - this->tickOffset);
}

void rr::components::TalonAdapter::Reset(){
    this->tickOffset = 0;
    this->talon->SetSelectedSensorPosition(0, 0, 10); // Resets the encoder itself
}