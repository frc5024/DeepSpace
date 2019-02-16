#include "Commands/Climb.h"

Climb::Climb() {
  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.

  // To run multiple commands at the same time,
  // use AddParallel()
  // e.g. AddParallel(new Command1());
  //      AddSequential(new Command2());
  // Command1 and Command2 will run in parallel.

  // A command group will require all of the subsystems that each member
  // would require.
  // e.g. if Command1 requires chassis, and Command2 requires arm,
  // a CommandGroup containing them would require both the chassis and the
  // arm.

	AddSequential ( new RaiseArms (0.5, 0.1 ));  //!< Touch arms to platform

	AddParallel		( new RaiseArms (0.63, 2  )); //!< Pull the front of the bot up onto the platform
	AddParallel		( new MoveLegsTo(MoveLegsTo::P_BOT, -1.0, 12.0)) ; //!< Move legs to bottom position
	AddSequential	( new Crawl     (1.00,  12 )); //!< Crawl onto the platform
	
	// Raise arm back up at 50% speed for 0.3 seconds
	AddSequential	(new RaiseArms(-0.5, 0.3));

	// Drive at 30% speed for half a second
	AddSequential	(new Drive(0.3, 0.5));

	// Bring legs back up
	AddSequential	(new RaiseLegs(1.00, 5));

  	//!< reset all hardware components
  	AddSequential	(new EndClimb  (0.03     ));
}
