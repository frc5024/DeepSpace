#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// Whenever possible, Macros and definitions are used in order to preserve memory

// Camera mappings
#define CAMERASERVER_FRONT_CAMERA 1
#define CAMERASERVER_BACK_CAMERA  0

// DriveTrain motors
#define DRIVETRAIN_LEFT_FRONT_MOTOR  1
#define DRIVETRAIN_LEFT_REAR_MOTOR   2
#define DRIVETRAIN_RIGHT_FRONT_MOTOR 3
#define DRIVETRAIN_RIGHT_REAR_MOTOR  4

// DriveTrain motor invertions
#define DRIVETRAIN_LEFT_FRONT_MOTOR_INVERT  false
#define DRIVETRAIN_LEFT_REAR_MOTOR_INVERT   false
#define DRIVETRAIN_RIGHT_FRONT_MOTOR_INVERT true
#define DRIVETRAIN_RIGHT_REAR_MOTOR_INVERT  true

// DriveWithJoystick Settings
#define DRIVEWITHJOYSTICK_ROTATION_LIMITER 0.95

// Light relay
#define LIGHT_RELAY 0 // Todo: put relay port here.

// Limit switches
#define LIMITSWITCH_ONE_PORT 4
#define LIMITSWITCH_TWO_PORT 3
// pins for hall effect:
// back bottom: 6
// back plastic (right): 5  
// top back: 1
// from botoom up

// front MIDDLE: 2
// front right strafe: 0
// front left: 3
// front arm left: 4

// optical sensor: 8

// Hall effect
#define BACK_BOTTOM_HALLEFFECT 6
#define BACK_RIGHT_TOP_HALLEFFECT 5
#define BACK_TOP_HALLEFFECT 1
#define FRONT_MIDDLE_HALLEFFECT 2

// Ultrasonic sensor
#define ULTRASONIC_PORT 1

// Xbox controllers
#define XBOX_CONTROLLER_DRIVE_PORT    0
#define XBOX_CONTROLLER_OPERATOR_PORT 1

// Handy macros to save Python programmers from going crazy
#define False false
#define True  true
#define elif  else if

// frc::GenericHID::JoystickHand is too long
#define Hand frc::GenericHID::JoystickHand

// Reasons why I shouldn't be allowed to program
#define WinGame(_class_) frc::StartRobot<_class_>()

#endif // _ROBOTMAP_HG_