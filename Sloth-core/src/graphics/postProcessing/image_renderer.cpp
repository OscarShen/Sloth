#include "image_renderer.h"

namespace sloth { namespace graphics {

	RawModel ImageRenderer::quad = RawModel();

	void ImageRenderer::renderQuad()
	{
		glBindVertexArray(quad.getVaoID());
		glEnableVertexAttribArray(0);
		glDisable(GL_DEPTH_TEST);

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glEnable(GL_DEPTH_TEST);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}

} }
