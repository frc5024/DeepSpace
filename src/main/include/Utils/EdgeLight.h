#ifndef UTILS_EDGELIGHT_HG
#define UTILS_EDGELIGHT_HG

#include <frc/Spark.h>
#include "RobotMap.h"

enum LedColour{
  kSOLID_WHITE =  93,
  kCHASE_RED   = -31,
  kCHASE_BLUE  = -29,
  kSOLID_GREEN =  75,
  kBEAT_BLUE   = -23,
  kBEAT_RED    = -25
};

namespace Utils{
    namespace EdgeLight{
        void Push();
        void Append(LedColour colour);

        extern LedColour ledbuffer;
        extern frc::Spark* pLEDController;
    } // namespace EdgeLight
}

#endif // _UTILS_EDGELIGHT_H