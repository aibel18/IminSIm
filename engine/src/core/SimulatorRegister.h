#ifndef XSIM_SIMULATOR_REGISTER_H
#define XSIM_SIMULATOR_REGISTER_H

#include "defines.h"
#include "SimulatorBase.h"

namespace xsim {

    class XSIM_API SimulatorRegister {
    private:
        static SimulatorBase* simulator;
    public:
        static void simulate(bool paused);
        static void setSimulator(SimulatorBase* newSimulator);
        static void cleanUp();
    };

}  // namespace xsim
#endif