#include <EntryBase.h>
#include "demos/mars_land.h"
#include "demos/spring_simulation.h"

BaseGame* createGame() {
  return new SpringSimulation();
  // return new MarsLand();
}
