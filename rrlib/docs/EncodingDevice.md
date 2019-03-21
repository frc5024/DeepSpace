# EncodingDevice
The EncodingDevice is a wrapper around many common encoders. It is designed to make working with encoders much easier.

## The Interface
All EncodingDevices have the same basic interface, but some adapters may have extra methods. The common methods are as follows:

| Method | Use |
| -- | -- |
| GetTicks() | Get the nimber of encoder ticks since last reset |
| GetCM() | Converts the output of GetTicks() to metric |
| GetInches() | Converts the output of GetTicks() to imperial |
| GetRevs() | Gets the number of full revolutions the encoded hardware has completed since the last reset |
| Reset() | Resets the encoder |

## Adapters
Many types of encoders use their own library or class. This makes hot-swapping hardware int the pits very hard. The goal of Adapters is to convert many different types of encoders to an EncodingDevice with the same interface

### TalonAdapter
A TalonAdapter takes any TalonSRX with an encoder attached and turns it into an EncodingDevice without any extra mathods. To adapt a TalonSRX to an EncodingDevice, do the following:
```cpp
// Encoder header
#include <rrlib/Components/Encoder.h>

// TalonSRX header
#include <ctre/Phoenix.h>

// Construct a TalonSRX on can ID 1
can::WPI_TalonSRX myMotor{1}; 

// Create EncodingDevice from myMotor
rr::componenets::EncodingDevice myEncoder = new rr::components::TalonAdapter(*myMotor, 25.35 /* wheel circumference */, 4096 /* Ticks per revolution on encoder */, false /* Is encoder wired backwards */);
```
