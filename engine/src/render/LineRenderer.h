#ifndef XSIM_LINE_RENDERER_H
#define XSIM_LINE_RENDERER_H

#include "defines.h"
#include "core/RenderRegister.h"
#include <vector>

namespace xsim {

	class XSIM_API LineRenderer {
	public:
		LineRenderer(std::vector<float>& data);
		~LineRenderer();

		float& getPoint(int index);

		void draw();
		void update();

	private:
		std::vector<float> data;
		u32 vao;
		u32 vbo;
	};

}  // namespace xsim
#endif