#include "SimulatorFactory.h"
#include "core/SimulatorRegister.h"
#include "simple/SimpleSimulator.h"

void xsim::SimulatorFactory::createInstance(SimulatorType type) {

    SimulatorRegister::cleanUp();

    // Register the simulators
    switch (type) {
        default:
            SimulatorRegister::setSimulator(new SimpleSimulator());
    }
}