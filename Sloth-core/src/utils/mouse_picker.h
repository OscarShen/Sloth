/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  MousePicker
 * @version 	:  v1.0.0
 * @description :  ��¼�ŵ�ǰ����Ӧλ�õķ��������͵���λ�õļ���
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��13��15:23:50
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_MOUSE_PICKER_H_
#define SLOTH_MOUSE_PICKER_H_

#include <sloth.h>
#include "camera/raw_camera.h"
#include "info/info.h"
#include "config/header.hpp"
#include "terrain/terrain.h"
namespace sloth {

	class MousePicker
	{
	private:
		glm::vec3 m_CurrentRay;

		glm::mat4 m_Projection;
		
		glm::mat4 m_View;

		const RawCamera &m_Camera;

		const Terrain &m_Terrain;

		glm::vec3 m_TerrainPosition;

	public:
		/************************************************************************
		* @description	: MousePicker�������ͶӰ����͵�����ص�
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��15:22:50
		***********************************************************************/
		MousePicker(const RawCamera &camera, const glm::mat4 &projection, const Terrain &terrain);

		/************************************************************************
		* @description	: ÿһ֡��������Ӧ�Ĺ��߷����Լ�����λ��
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��15:20:13
		***********************************************************************/
		void update();

		/************************************************************************
		* @description	: ��ȡ��ǰ���λ�÷����Ĺ��ߵķ�������
		* @author		: Oscar Shen
		* @creat		: 2017��2��12��19:26:55
		***********************************************************************/
		inline glm::vec3 getCurrentRay() const { return m_CurrentRay; }

		/************************************************************************
		* @description	: ��ȡ��ǰ���λ�õ��ε���������
		* @author		: Oscar Shen
		* @creat		: 2017��2��12��19:28:43
		***********************************************************************/
		inline glm::vec3 getCurrentTerrainPosition() const { return m_TerrainPosition; }


	private:
		/************************************************************************
		* @description	: ��Ⱦ�����������ȡ�����߷���
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��15:21:01
		***********************************************************************/
		glm::vec3 calculateMouseRay();

		/************************************************************************
		* @description	: �������camera����Ϊdistance������Ϊray_dir�ĵ�
		* @author		: Oscar Shen
		* @creat		: 2017��2��12��19:39:32
		***********************************************************************/
		inline glm::vec3 getPointOnRay(const glm::vec3 &ray_dir, float distance) const {
			return ray_dir * distance + m_Camera.getPosition();
		}

		/************************************************************************
		* @description	: ���ַ��������ձƽ����������ͼ�ཻλ��
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��10:52:47
		***********************************************************************/
		glm::vec3 binarySearch(int count, float start, float finish, const glm::vec3 &ray);

		/************************************************************************
		* @description	: ���start���ڵ���֮����finish���ڵ���֮�£��򷵻�true
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��10:52:47
		***********************************************************************/
		bool intersectionInRange(float start, float finish, const glm::vec3 &ray) const;

		/************************************************************************
		* @description	: �ж�һ��������ε���Ը߶ȣ��ڵ���֮�·���true,���򷵻�false
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��15:22:06
		***********************************************************************/
		inline bool isUnderGround(const glm::vec3 &testPoint) const {
			// TODO!���ʹ���˶���Σ������޸�����
			// Terrain &terrain = getTerrain(testPoint.x,testPoint.z)
			//height = terrain.getHeightOfTerrain(testPoint.x, testPoint.z);
			//return testPoint.y < height ? true : false;
			return testPoint.y < m_Terrain.getHeightOfTerrain(testPoint.x, testPoint.z) ? true : false;
		}
	};

} 


#endif // !SLOTH_MOUSE_PICKER_H_

