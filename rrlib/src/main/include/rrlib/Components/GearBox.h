#ifndef _RR_COMPONENTS_GEARBOX_H
#define _RR_COMPONENTS_GEARBOX_H

#include <ctre/Phoenix.h>
#include <frc/SpeedController.h>
#include <frc/DigitalInput.h>
#include <rrlib/Components/Encoder.h>

namespace rr {
    namespace components {
        struct GearBox{
            frc::SpeedController *motor;
            rr::components::EncodingDevice *sensor;
            frc::DigitalInput *digitalLimits[10];
        };
    }
}
#endif