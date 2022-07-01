#include "iminsim_engine.h"
#include <idl_logger.h>

using namespace iminsim;

Engine::Engine() {
	idl::Platform platform;
	LOG_INFO("Hello info")
	LOG_WARN("hello warn")
	LOG_ERROR("hello error")
	LOG_DEBUG("hello debug")
}