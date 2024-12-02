#ifndef XSIM_LINE_RENDERER_H
#define XSIM_LINE_RENDERER_H

#include "defines.h"
#include "core/RenderRegister.h"

namespace xsim {

	class XSIM_API LineRenderer : public BaseRenderer {
	public:
		LineRenderer(std::vector<float>& data);
        LineRenderer(std::vector<vec3>& data);
		~LineRenderer();

		vec3& point(int index);
		inline int pointSize() const;
        void init() override;
		void draw() override;
		void update() override;

	private:
		u32 vao;
		u32 vbo;
	};

    inline int xsim::LineRenderer::pointSize() const {
        return data.size();
    }

}  // namespace xsim
#endif