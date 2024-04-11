#ifndef XSIM_CONTEXT_CONFIG_H
#define XSIM_CONTEXT_CONFIG_H

#include "defines.h"

namespace xsim {

	struct ContextConfig {
		// Render Type
		// idl::GraphicRenderType type; // TODO: define type on engine

		// Context major version
		int major;

		// Context minor version
		int minor;
	};
}  // namespace xsim
#endif