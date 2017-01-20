#include "global_function.h"

namespace sloth { namespace graphics {
	void enable_culling()
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	void disable_culling()
	{
		glDisable(GL_CULL_FACE);
	}

} }

