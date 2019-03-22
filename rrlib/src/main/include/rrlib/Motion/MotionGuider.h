#ifndef _RR_MOTION_MOTIONGUIDER_H
#define _RR_MOTION_MOTIONGUIDER_H

#include <ctre/Phoenix.h>

namespace rr {
    namespace motion {

        class MotionGuider{
            public:
              MotionGuider(can::WPI_TalonSRX *talon, int ticksPerRev, double range);
              void Feed(double input);
            //   void SetSmoothing(int smooth);

            private:
              can::TalonSRX *talon;
              double range;
              int tpr;
        };

    } // namespace motion
}

#endif // _RR_MOTION_MOTIONGUIDER_H