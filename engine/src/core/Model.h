#ifndef XSIM_MODEL_H
#define XSIM_MODEL_H

// #include "defines.h
#include "physics/Particle.h"
#include "BaseRenderer.h"

namespace xsim {

    class XSIM_API Model {
    public:
        std::vector<Particle> in_particle;
        std::vector<vec3> out_position;
        BaseRenderer* renderer;

        void addParticle(Particle);
        void addRenderer(BaseRenderer*);
    };

}  // namespace xsim
#endif