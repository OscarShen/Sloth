/************************************************************************ 
 * @project 	:  $rootnamespace$
 * @class   	:  $safeitemrootname$
 * @version 	:  v1.0.0
 * @description :  
 * @author		:  $username$
 * @creat 		:  $time$
 * @revise 		:  $time$
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_UNIFORM_H_
#define SLOTH_UNIFORM_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace sloth {

	class Uniform
	{
	private:
		static const int NOT_FOUND = -1;
		std::string m_Name; // 变量名
		int m_Location; // OpenGL 位置
		unsigned int m_ProgramID; // 属于哪一个 shader 程序

	public:
		Uniform(const std::string &name);

		void storeUniformLocation(unsigned int programID);

		inline int getLocation() const { return m_Location; }

		inline unsigned int getProgramID() const { return m_ProgramID; }
	};

	class UniformBool : public Uniform
	{
	private:
		bool m_CurrentBool;
		bool m_Used = false;

	public:
		UniformBool(const std::string &name);

		void loadBool(bool b);
	};

	class UniformFloat : public Uniform
	{
	private:
		float m_CurrentValue;
		bool m_Used = false;

	public:
		UniformFloat(const std::string &name);

		void loadFloat(float value);
	};

	class UniformMatrix4 : public Uniform
	{
	public:
		UniformMatrix4(const std::string &name);

		void loadMatrix4(const glm::mat4 &matrix);
	};

	class UniformSampler : public Uniform
	{
	private:
		int m_CurrentValue;
		bool m_Used = false;

	public:
		UniformSampler(const std::string &name);

		void loadTexUnit(int texUnit);
	};

	class UniformVec2 : public Uniform
	{
	private:
		float m_X;
		float m_Y;
		bool m_Used = false;

	public:
		UniformVec2(const std::string &name);

		void loadVec2(const glm::vec2 &vector);

		void loadVec2(float x, float y);
	};

	class UniformVec3 : public Uniform
	{
	private:
		float m_X;
		float m_Y;
		float m_Z;
		bool m_Used = false;

	public:
		UniformVec3(const std::string &name);

		void loadVec3(const glm::vec3 &vector);

		void loadVec3(float x, float y, float z);
	};

	class UniformVec4 : public Uniform
	{
	private:
		float m_X;
		float m_Y;
		float m_Z;
		float m_W;
		bool m_Used = false;

	public:
		UniformVec4(const std::string &name);

		void loadVec4(const glm::vec4 &vector);

		void loadVec4(float x, float y, float z, float w);
	};

} 


#endif // !SLOTH_UNIFORM_H_
