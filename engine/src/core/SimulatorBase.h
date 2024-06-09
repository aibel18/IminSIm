#ifndef XSIM_SIMULATOR_BASE_H
#define XSIM_SIMULATOR_BASE_H

#include "defines.h"

namespace xsim {

    class XSIM_API SimulatorBase {
    public:
        SimulatorBase();
        virtual ~SimulatorBase() = 0;

        virtual void step() = 0;

    protected:
        virtual void init() = 0;

        friend class SimulatorRegister;
    };

}  // namespace xsim
#endif