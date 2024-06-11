#include "SimpleSimulator.h"
#include "util/logger.h"

xsim::SimpleSimulator::SimpleSimulator() {
}
xsim::SimpleSimulator::~SimpleSimulator() {
}
void xsim::SimpleSimulator::step() {
    LOG_INFO("run step of Simulator %p", this);
}

void xsim::SimpleSimulator::init() {
}
