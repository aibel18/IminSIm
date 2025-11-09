#ifndef XSIM_SIMULATOR_BASE_H
#define XSIM_SIMULATOR_BASE_H

#include "defines.h"
#include "Model.h"

namespace xsim {

    class XSIM_API SimulatorBase {
    public:
        SimulatorBase();
        virtual ~SimulatorBase() = 0;

        void addModel(Model& model);
        void updateOutPosition();

        float r = 0.f;
        float s = 0.005f;
        float stiffness = 0.01f;
        float dt = 0.005f;

    protected:
        std::vector<Model> models;
        virtual void init() = 0;
        virtual void step() = 0;

        friend class SimulatorRegister;
    };

}  // namespace xsim
#endif