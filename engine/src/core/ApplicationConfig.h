#ifndef XSIM_APPLICATION_CONFIG_H
#define XSIM_APPLICATION_CONFIG_H

#include "defines.h"

namespace xsim {

	struct ApplicationConfig {
		// Application name used in windowing
		const char* name;

		// Window initial width
		int width;

		// Window initial height
		int height;
	};
}  // namespace xsim
#endif