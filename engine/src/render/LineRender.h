#ifndef XSIM_RENDER_LINE_H
#define XSIM_RENDER_LINE_H

#include "defines.h"
#include "core/RenderRegister.h"
#include <vector>

namespace xsim {

	class XSIM_API LineRender {
	public:
		LineRender(std::vector<float>& data);
		~LineRender();

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