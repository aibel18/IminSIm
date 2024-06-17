#include "SimulatorRegister.h"
#include "util/logger.h"

xsim::SimulatorBase* xsim::SimulatorRegister::simulator;

void xsim::SimulatorRegister::simulate(bool paused) {
    if (simulator && paused)
        simulator->step();
}

void xsim::SimulatorRegister::setSimulator(SimulatorBase* newSimulator) {
    // safely an unique simulator instance
    SimulatorRegister::cleanUp();
    simulator = newSimulator;
}

void xsim::SimulatorRegister::cleanUp() {
    if (simulator) {
        delete simulator;
    }
}
