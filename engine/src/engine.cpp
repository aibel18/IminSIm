#include "engine.h"
#include "logger.h"

using namespace xsim;

Engine::Engine() {
	LOG_INFO("Hello info")
	LOG_WARN("hello warn")
	LOG_ERROR("hello error")
	LOG_DEBUG("hello debug")
}