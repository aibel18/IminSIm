#ifndef XSIM_APPLICATION_H
#define XSIM_APPLICATION_H

#include "defines.h"
#include "ApplicationConfig.h"

namespace xsim {

	class XSIM_API Application {
	private:
		ApplicationConfig *config;

	public:
		Application();
		bool create(ApplicationConfig *config);
		bool run();
	};
}  // namespace xsim
#endif