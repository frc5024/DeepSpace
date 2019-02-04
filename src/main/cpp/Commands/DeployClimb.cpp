#include "Commands/DeployClimb.h"
#include "Commands/DeployArm.h"
#include "Commands/DeployLeg.h"

DeployClimb::DeployClimb() {
  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.
  AddSequential(new DeployArm(2, 0.2));
  AddParallel(new DeployLeg(4, 0.8));
  AddSequential(new DeployArm(4, 0.1));
}
