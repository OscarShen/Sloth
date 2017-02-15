/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  MousePicker
 * @version 	:  v1.0.0
 * @description :  记录着当前鼠标对应位置的方向向量和地形位置的计算
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月13日15:23:50
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_MOUSE_PICKER_H_
#define SLOTH_MOUSE_PICKER_H_

#include <glm/glm.hpp>
#include "../graphics/camera/raw_camera.h"
#include "../graphics/info/info.h"
#include "../config/macro.h"
#include "../graphics/terrain/terrain.h"
namespace sloth { namespace util {

	class MousePicker
	{
	private:
		glm::vec3 m_CurrentRay;

		glm::mat4 m_Projection;
		
		glm::mat4 m_View;

		// 保留 camera 的引用，要保证 camera 的生存期比 mousepicker 要长
		const graphics::RawCamera &m_Camera;

		const graphics::Terrain &m_Terrain;

		glm::vec3 m_TerrainPosition;

	public:
		/************************************************************************
		* @description	: MousePicker是相机、投影矩阵和地形相关的
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日15:22:50
		***********************************************************************/
		MousePicker(const graphics::RawCamera &camera, const glm::mat4 &projection, const graphics::Terrain &terrain);

		/************************************************************************
		* @description	: 每一帧更新鼠标对应的光线方向以及地形位置
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日15:20:13
		***********************************************************************/
		void update();

		/************************************************************************
		* @description	: 获取向当前鼠标位置发出的光线的方向向量
		* @author		: Oscar Shen
		* @creat		: 2017年2月12日19:26:55
		***********************************************************************/
		inline glm::vec3 getCurrentRay() const { return m_CurrentRay; }

		/************************************************************************
		* @description	: 获取向当前鼠标位置地形的世界坐标
		* @author		: Oscar Shen
		* @creat		: 2017年2月12日19:28:43
		***********************************************************************/
		inline glm::vec3 getCurrentTerrainPosition() const { return m_TerrainPosition; }


	private:
		/************************************************************************
		* @description	: 渲染管线逆过程提取鼠标光线方向
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日15:21:01
		***********************************************************************/
		glm::vec3 calculateMouseRay();

		/************************************************************************
		* @description	: 计算距离camera距离为distance，方向为ray_dir的点
		* @author		: Oscar Shen
		* @creat		: 2017年2月12日19:39:32
		***********************************************************************/
		inline glm::vec3 getPointOnRay(const glm::vec3 &ray_dir, float distance) const {
			return ray_dir * distance + m_Camera.getPosition();
		}

		/************************************************************************
		* @description	: 二分法返回最终逼近的视线与地图相交位置
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日10:52:47
		***********************************************************************/
		glm::vec3 binarySearch(int count, float start, float finish, const glm::vec3 &ray);

		/************************************************************************
		* @description	: 如果start点在地面之上且finish点在地面之下，则返回true
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日10:52:47
		***********************************************************************/
		bool intersectionInRange(float start, float finish, const glm::vec3 &ray) const;

		/************************************************************************
		* @description	: 判断一个点与地形的相对高度，在地形之下返回true,否则返回false
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日15:22:06
		***********************************************************************/
		inline bool isUnderGround(const glm::vec3 &testPoint) const {
			// TODO!如果使用了多地形，可以修改如下
			// Terrain &terrain = getTerrain(testPoint.x,testPoint.z)
			//height = terrain.getHeightOfTerrain(testPoint.x, testPoint.z);
			//return testPoint.y < height ? true : false;
			return testPoint.y < m_Terrain.getHeightOfTerrain(testPoint.x, testPoint.z) ? true : false;
		}
	};

} }


#endif // !SLOTH_MOUSE_PICKER_H_

