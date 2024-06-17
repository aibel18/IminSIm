#ifndef XSIM_SIMULATOR_REGISTER_H
#define XSIM_SIMULATOR_REGISTER_H

#include "defines.h"
#include "physics/SimulatorBase.h"

namespace xsim {

    class XSIM_API SimulatorRegister {
    public:
        static SimulatorBase* simulator;
    public:
        static void simulate(bool paused);
        static void setSimulator(SimulatorBase* newSimulator);
        static void cleanUp();
    };

}  // namespace xsim
#endif