#include "Commands/DeployClimb.h"
#include "Commands/DeployArm.h"
#include "Commands/DeployLeg.h"

DeployClimb::DeployClimb() {
  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.
  AddSequential(new DeployArm(2));
  AddParallel(new DeployLeg(4));
  AddSequential(new DeployArm(4));
}
