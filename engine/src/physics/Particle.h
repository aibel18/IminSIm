#ifndef XSIM_PARTICLE_H
#define XSIM_PARTICLE_H

#include "defines.h"
#include "math/math_defines.h"
#include <vector>

namespace xsim {

    struct XSIM_API Particle {
        f32 mass;

        // scalar vars
        f32 density;
        f32 pressure;

        // vectorial vars
        vec3 position;
        vec3 velocity;
        vec3 acceleration;
    };

    typedef std::vector<Particle> Model;

}  // namespace xsim
#endif