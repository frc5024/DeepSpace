#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// Whenever possible, Macros and definitions are used in order to preserve memory

// Robot configurations
#define ROBOT_CYCLE_TIME    0.02 ///< Milliseconds delay between each periodic call

// Camera mappings
#define CAMERASERVER_DRIVER_CAMERA 1
#define CAMERASERVER_VISION_CAMERA 0

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

#define DRIVETRAIN_RADIAL_SENSITIVITY_CUTOFF 0.8

// Slider
#define SLIDER_MOTOR 5

// DriveWithJoystick Settings
#define DRIVEWITHJOYSTICK_ROTATION_LIMITER 0.95

// Xbox controllers
#define XBOX_CONTROLLER_DRIVE_PORT    0
#define XBOX_CONTROLLER_OPERATOR_PORT 1

// AutoTurn PID values
#define PID_TWEAK_P     0.030   ///< Multiplier used to bring the proportional value to a motor output
#define PID_TWEAK_I     0.025   ///< Multiplier used to bring the integral value to a motor output 
#define PID_TWEAK_D     0.001   ///< Multiplier used to bring the derivative value to a motor output
#define PID_BUFFER      2       ///< Degrees plus-or-minus range from target robot can be off of and still stop

// Handy macros to save Python programmers from going crazy
#define False false
#define True  true
#define elif  else if

// frc::GenericHID::JoystickHand is too long
#define Hand frc::GenericHID::JoystickHand

// Reasons why I shouldn't be allowed to program
#define WinGame(_class_) frc::StartRobot<_class_>()

#endif // _ROBOTMAP_HG_