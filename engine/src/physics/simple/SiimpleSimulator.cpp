#include "SimpleSimulator.h"
#include "util/logger.h"

xsim::SimpleSimulator::SimpleSimulator() {
}
xsim::SimpleSimulator::~SimpleSimulator() {
}
void xsim::SimpleSimulator::step() {
    for (auto model : models) {
        for (auto p : model) {
            LOG_INFO("position: %f %f %f", p.position.x, p.position.y, p.position.z);
        }
    }
}

void xsim::SimpleSimulator::init() {
}
