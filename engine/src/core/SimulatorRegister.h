#ifndef XSIM_SIMULATOR_REGISTER_H
#define XSIM_SIMULATOR_REGISTER_H

#include "defines.h"
#include "SimulatorBase.h"

namespace xsim {

    class XSIM_API SimulatorRegister {
    public:
        static SimulatorBase* simulator;
    };

}  // namespace xsim
#endif