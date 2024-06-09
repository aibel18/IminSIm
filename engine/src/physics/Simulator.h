#ifndef XSIM_SIMULATOR_H
#define XSIM_SIMULATOR_H

#include "core/SimulatorBase.h"

namespace xsim {

    class Simulator : public SimulatorBase {
    public:
        Simulator();
        virtual ~Simulator();

        void step();

    protected:
        void init();
    };

}  // namespace xsim
#endif