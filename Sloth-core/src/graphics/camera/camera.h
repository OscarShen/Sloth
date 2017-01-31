#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "raw_camera.h"
#include "../info/info.h"
#include "../../utils/timer.h"

namespace sloth { namespace graphics {

	enum CameraMovement
	{
		MOVEFORWARD,
		MOVEBACKWARD,
		MOVELEFT,
		MOVERIGHT
	};
	class SlothWindow;
	class Camera : public RawCamera
	{
	public:
		Camera() : RawCamera() {}

		virtual ~Camera() {}

		virtual void process(SlothWindow * window) override;

	private:
		void process_keyboard(SlothWindow * window);

		void do_movement(CameraMovement direction, float deltaTime);

		void process_mouse(SlothWindow * window);

		void do_mouse(double xOffSet, double yOffSet);
	};

} }