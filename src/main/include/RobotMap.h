#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// Whenever possible, Macros and definitions are used in order to preserve memory

// Robot values
#define ROBOT_CYCLE_TIME	0.02

// RadialTurn
#define RADIAL_LENGTH				666 // TODO: Measure: Horizontal distance from camera to front bumper
#define RADIAL_WIDTH_WHEEL_2		666 // TODO: Measure: Horizontal distance from left side wheels to right side wheels divided by two

// Camera mappings
#define CAMERASERVER_DRIVER_CAMERA		1
#define CAMERASERVER_VISION_CAMERA		0

// DriveTrain motors
#define DRIVETRAIN_LEFT_FRONT_MOTOR		1
#define DRIVETRAIN_LEFT_REAR_MOTOR		2
#define DRIVETRAIN_RIGHT_FRONT_MOTOR	3
#define DRIVETRAIN_RIGHT_REAR_MOTOR		4

// DriveTrain motor invertions
#define DRIVETRAIN_LEFT_FRONT_MOTOR_INVERT	false
#define DRIVETRAIN_LEFT_REAR_MOTOR_INVERT	false
#define DRIVETRAIN_RIGHT_FRONT_MOTOR_INVERT	true
#define DRIVETRAIN_RIGHT_REAR_MOTOR_INVERT	true

#define DRIVETRAIN_RADIAL_SENSITIVITY_CUTOFF	0.8

// Slider
#define SLIDER_MOTOR	5

// DriveWithJoystick Settings
#define DRIVEWITHJOYSTICK_ROTATION_LIMITER	0.95

// Xbox controllers
#define XBOX_CONTROLLER_DRIVE_PORT		0
#define XBOX_CONTROLLER_OPERATOR_PORT	1

// Handy macros to save Python programmers from going crazy
#define False false
#define True  true
#define elif  else if

// frc::GenericHID::JoystickHand is too long
#define Hand frc::GenericHID::JoystickHand

// Reasons why I shouldn't be allowed to program
#define WinGame(_class_) frc::StartRobot<_class_>()

#endif // _ROBOTMAP_HG_