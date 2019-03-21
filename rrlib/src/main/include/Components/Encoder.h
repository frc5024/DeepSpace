#ifndef _RR_COMPONENTS_ENCODER_H
#define _RR_COMPONENTS_ENCODER_H

#include <ctre/Phoenix.h>

namespace rr {
    namespace components {

        class EncodingDevice{
            public:
              EncodingDevice(double circumferenceCM);
              double GetCM();
              double GetInch();
              double GetRevs();
              virtual void Reset();
              virtual int GetTicks();
              int tickOffset;
              int tpr;

            private:
              double circumference;
        };

        class TalonAdapter : public EncodingDevice {
            public:
              TalonAdapter(can::WPI_TalonSRX *talon, double circumferenceCM, int ticksPerRev, bool invert) ;
              int GetTicks() override;
              void Reset() override;

            private:
              can::WPI_TalonSRX *talon;
              double invert;
        };
    } // namespace components
}


#endif // _RR_COMPONENTS_ENCODER_H