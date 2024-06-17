#ifndef XSIM_SIMPLE_SIMULATOR_H
#define XSIM_SIMPLE_SIMULATOR_H

#include "physics/SimulatorBase.h"

namespace xsim {

    class SimpleSimulator : public SimulatorBase {
    public:
        SimpleSimulator();
        virtual ~SimpleSimulator();

    protected:
        void step();
        void init();
    };

}  // namespace xsim
#endif