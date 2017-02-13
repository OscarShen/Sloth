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
		// ��ȡ���λ��
		float mouseX = (float) graphics::Input::cursorPosX;
		float mouseY = (float) graphics::Input::cursorPosY;
		// �����λ��ת��ΪOpenGL��NDC����
		auto normalizedCoord = glm::vec2((2.0f * mouseX) / SCREEN_WIDTH - 1.0f, 1.0f - (2.0f * mouseY) / SCREEN_HEIGHT);
		// ��NDC����ת��ΪͶӰ�����꣬���ڲ���Ҫ��ȣ�����Ҫ��ȫ
		// ����͸�ӳ�������z��Ϊ-1.0f����
		auto clipCoord = glm::vec4(normalizedCoord, -1.0f, 1.0f);
		// ��ͶӰ������ת��Ϊ����ռ䣬
		// ���ڲ�������ȣ���Ҫ��z������Ϊ-1.0f
		// ��ʱ������ֻ���淽�򣬹ʽ�w������Ϊ0.0f
		auto cameraCoord = glm::inverse(m_Projection) * clipCoord;
		cameraCoord.z = -1.0f;
		cameraCoord.w = 0.0f;
		// ������ռ�����ת��Ϊ��������
		auto worldCoord = glm::inverse(m_View) * cameraCoord;
		// ֻ��Ҫ�������������ص�λ����
		return glm::normalize(glm::vec3(worldCoord.x, worldCoord.y, worldCoord.z));
	}

	glm::vec3 MousePicker::binarySearch(int count, float start, float finish, const glm::vec3 & ray)
	{
		int times = 0;
		float half = start + (finish - start) / 2.0f;
		while (count != times) {
			// TODO!���ͼ�������ж�
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
		// ���start���ڵ���֮����finish���ڵ���֮�£��򷵻�true
		return !isUnderGround(getPointOnRay(ray, start)) &&
			isUnderGround(getPointOnRay(ray, finish)) ? true : false;
	}

} }
