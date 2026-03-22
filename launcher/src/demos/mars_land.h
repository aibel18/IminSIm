#ifndef LAUNCHER_MARS_LAND_H
#define LAUNCHER_MARS_LAND_H

#include "core/BaseGame.h"
#include "math/math_defines.h"
// #include "core/SimulatorRegister.h" // TODO: improve call to headers
// #include "physics/SimulatorFactory.h"
// #include "physics/Particle.h"

class MarsLand : public xsim::BaseGame {

  public:
    MarsLand();
    
    void init() override;
    void update() override;
    void onResize(int width, int height) override;
};

#endif
