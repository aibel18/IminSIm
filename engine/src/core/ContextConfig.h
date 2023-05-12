#ifndef XSIM_CONTEXT_CONFIG_H
#define XSIM_CONTEXT_CONFIG_H

#include "defines.h"
#include <idl_context.h>

namespace xsim {

	struct ContextConfig {
		// Render Type
		idl::GraphicRender type;

		// Context major version
		int major;

		// Context minor version
		int minor;
	};
}  // namespace xsim
#endif