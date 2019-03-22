#include <rrlib/Motion/MotionGuider.h>

rr::motion::MotionGuider::MotionGuider(can::WPI_TalonSRX *talon, int ticksPerRev, double range){
    this->talon = talon;
    this->tpr = ticksPerRev;
    this->range = range;
    this->talon->SetSelectedSensorPosition(0, 0, 10);
}

void rr::motion::MotionGuider::Feed(double input){
    double targetPos = input * this->tpr * this->range;
    this->talon->Set(ControlMode::MotionMagic, targetPos);
}

// void rr::motion::MotionGuider::SetSmoothing(int smooth){
//     if(smooth > 8) smooth = 8;
//     if(smooth < 0) smooth = 0;
//     this->talon->ConfigMotionSCurveStrength(smooth, 0);
// }