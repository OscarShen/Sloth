#include "mouse_picker.h"

namespace sloth { namespace util {
	MousePicker::MousePicker(const graphics::RawCamera & camera, const glm::mat4 & projection, const graphics::Terrain &terrain)
		:m_Projection(projection), m_Camera(camera), m_Terrain(terrain)
	{
		m_View = camera.getViewMatrix();
		m_CurrentRay = calculateMouseRay();
	}

	void MousePicker::update()
	{
		m_View = m_Camera.getViewMatrix();
		m_CurrentRay = calculateMouseRay();
		if (intersectionInRange(0.0f, MOUSE_PICKER_RAY_CASTING_RANGE, m_CurrentRay)) {
			m_TerrainPosition = binarySearch(MOUSE_PICKER_RECURSION_COUNT, 0.0f, MOUSE_PICKER_RAY_CASTING_RANGE, m_CurrentRay);
		}
	}

	glm::vec3 MousePicker::calculateMouseRay()
	{
		// 获取鼠标位置
		float mouseX = (float) graphics::Input::cursorPosX;
		float mouseY = (float) graphics::Input::cursorPosY;
		// 将鼠标位置转换为OpenGL内NDC坐标
		auto normalizedCoord = glm::vec2((2.0f * mouseX) / SCREEN_WIDTH - 1.0f, 1.0f - (2.0f * mouseY) / SCREEN_HEIGHT);
		// 将NDC坐标转换为投影后坐标，由于不需要深度，不需要完全
		// 逆向透视除法，将z设为-1.0f即可
		auto clipCoord = glm::vec4(normalizedCoord, -1.0f, 1.0f);
		// 将投影后坐标转换为相机空间，
		// 由于不保存深度，需要将z分量设为-1.0f
		// 此时的向量只保存方向，故将w分量设为0.0f
		auto cameraCoord = glm::inverse(m_Projection) * clipCoord;
		cameraCoord.z = -1.0f;
		cameraCoord.w = 0.0f;
		// 将相机空间坐标转换为世界坐标
		auto worldCoord = glm::inverse(m_View) * cameraCoord;
		// 只需要三个分量，返回单位向量
		return glm::normalize(glm::vec3(worldCoord.x, worldCoord.y, worldCoord.z));
	}

	glm::vec3 MousePicker::binarySearch(int count, float start, float finish, const glm::vec3 & ray)
	{
		int times = 0;
		float half = start + (finish - start) / 2.0f;
		while (count != times) {
			// TODO!多地图集增加判断
			// Terrain *terrain = getTerrain(...)
			if (intersectionInRange(start, half, ray)) {
				++times;
				finish = half;
			}
			else {
				++times;
				start = half;
			}
			half = start + (finish - start) / 2.0f;
		}
		return getPointOnRay(ray, half);
	}

	bool MousePicker::intersectionInRange(float start, float finish, const glm::vec3 & ray) const
	{
		// 如果start点在地面之上且finish点在地面之下，则返回true
		return !isUnderGround(getPointOnRay(ray, start)) &&
			isUnderGround(getPointOnRay(ray, finish)) ? true : false;
	}

} }
