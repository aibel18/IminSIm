#ifndef XSIM_POINT_RENDERER_H
#define XSIM_POINT_RENDERER_H

#include "defines.h"
#include "core/RenderRegister.h"

namespace xsim {

	class XSIM_API PointRenderer : public BaseRenderer {
	public:
		PointRenderer(std::vector<float>& data);
    PointRenderer(std::vector<vec3>& data);
		~PointRenderer();

		vec3& point(int index);
		inline int pointSize() const;
    void init() override;
		void draw() override;
		void update() override;

	private:
		u32 vao;
		u32 vbo;
	};

	inline int xsim::PointRenderer::pointSize() const {
		return data.size();
	}

}  // namespace xsim
#endif
