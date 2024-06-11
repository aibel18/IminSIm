#ifndef XSIM_SIMULATOR_FACTORY_H
#define XSIM_SIMULATOR_FACTORY_H

#include "defines.h"

namespace xsim {

    enum SimulatorType {
		SIMPLE,
		PBD
	};

    class XSIM_API SimulatorFactory {
    public:
        static void createInstance(SimulatorType type = SIMPLE);
    };

}  // namespace xsim
#endif