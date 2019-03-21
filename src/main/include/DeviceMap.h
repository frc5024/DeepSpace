#ifndef _DEVICEMAP_H
#define _DEVICEMAP_H

#include <ctre/Phoenix.h>
#include <frc/Spark.h>

struct DtiveTrain{
    can::WPI_TalonSRX LeftFront{1};
    can::WPI_TalonSRX LeftRear{2};

    can::WPI_TalonSRX RightFront{3};
    can::WPI_TalonSRX RightRear{4};
};

struct Slider{
    frc::Spark Motor{0};
};

#endif //_DEVICEMAP_H