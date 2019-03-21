# GearBox (rr::components::GearBox)
The GearBox is a struct that packages together an [frc::SpeedController](http://first.wpi.edu/FRC/roborio/release/docs/cpp/classfrc_1_1SpeedController.html) and an [rr::components::EncodingDevice](./EncodingDevice.html).

## Basic GearBox with TalonSRX and no encoder
The most basic GearBox is made up of only a motor controller and does not contain an encoder.
```cpp
// GearBox header
#include <rrlib/Components/GearBox.h>

// TalonSRX header
#include <ctre/Phoenix.h>

// Construct a TalonSRX on can ID 1
can::WPI_TalonSRX myMotor{1}; 

// Create a GearBox
rr::components::GearBox *myGearBox;
myGearBox->motor = new frc::SpeedControllerGroup(*myMotor);
```

## GearBox with two TalonSRX motor controllers and a TalonSRX-based EncodingDevice
This example is how our drivetrain GearBoxes are set up.
```cpp
// GearBox header
#include <rrlib/Components/GearBox.h>

// TalonSRX header
#include <ctre/Phoenix.h>

// Encoder header
#include <rrlib/Components/Encoder.h>

// Construct a TalonSRX on can ID 1
can::WPI_TalonSRX frontMotor{1}; 

// Construct a TalonSRX on can ID 2
can::WPI_TalonSRX backMotor{2}; 

// Create a GearBox
rr::components::GearBox *myGearBox;
myGearBox->motor = new frc::SpeedControllerGroup(*frontMotor, *backMotor);
myGearBox->sensor = new rr::components::TalonAdapter(*frontMotor, 25.35 /* wheel circumference */, 4096 /* Ticks per revolution on encoder */, false /* Is encoder wired backwards */);
```

## GearBox Motors
The GearBox motor is just an [frc::SpeedController](http://first.wpi.edu/FRC/roborio/release/docs/cpp/classfrc_1_1SpeedController.html). This can be any WPIlib motor controller, or a group of motor controllers created with an [frc::SpeedControllerGroup](http://first.wpi.edu/FRC/roborio/release/docs/cpp/classfrc_1_1SpeedControllerGroup.html)

## GearBox Sensors
The GearBox sensor is not required to make a functional GearBox. It is just one of rrlib's [rr::components::EncodingDevice](./EncodingDevice.html)es. These are wrappers around various types of encoders and are further explained in the EncodingDevice documentation.