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

  AddSequential( new Crawl     (100, 1 ));
  AddParallel  ( new HoldArms  (1      ));
  AddParallel  ( new HoldLegs  (1.5    ));
  AddSequential( new RaiseArms (30, 1  ));
  AddSequential( new Drive     (30, 0.5));
  AddParallel  ( new EndClimb  (0.03   ));
}
