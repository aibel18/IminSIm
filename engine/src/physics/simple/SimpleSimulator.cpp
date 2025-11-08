#include "SimpleSimulator.h"
#include "util/logger.h"

xsim::SimpleSimulator::SimpleSimulator() {
}
xsim::SimpleSimulator::~SimpleSimulator() {
}
void xsim::SimpleSimulator::step() {
    for (auto &model : models) {
        for (auto &p : model.in_particle) {
            p.position.x += 0.0009;
            // LOG_INFO("particle[%p] position: %f %f %f", &p, p.position.x, p.position.y, p.position.z);
        }
    }
}

void xsim::SimpleSimulator::init() {
}
