#ifndef XSIM_LINE_RENDERER_H
#define XSIM_LINE_RENDERER_H

#include "defines.h"
#include "core/RenderRegister.h"
#include <vector>
#include "math/math_defines.h"

namespace xsim {

	class XSIM_API LineRenderer : public BaseRenderer {
	public:
		LineRenderer(std::vector<float>& data);
        LineRenderer(std::vector<vec3>& data);
		~LineRenderer();

		vec3& getPoint(int index);
        void init() override;
		void draw() override;
		void update();

	private:
		std::vector<vec3> data;
		u32 vao;
		u32 vbo;
	};

}  // namespace xsim
#endif