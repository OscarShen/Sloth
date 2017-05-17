/************************************************************************ 
 * @description :  
 * @author		:  $username$
 * @creat 		:  $time$
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_H_
#define SLOTH_H_
#include <algorithm>
#include <memory>
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <map>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <SOIL/SOIL.h>

namespace sloth {
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#define CHECK_INFO(x, str) if(!(x)) { std::cout << (str) << "\n\t|file: "<< __FILE__<<",line: " << __LINE__<<std::endl;}
#define CHECK(x) CHECK_INFO(x, "check equal failed!")
#define CHECK_EQ(x, y) if((x)!=(y)) { std::cout << "check equal failed!" << "\n\t|file: "<< __FILE__<<",line: " << __LINE__<<std::endl; }
#define CHECK_NE(x, y) if((x)==(y)) { std::cout << "check not equal failed!" << "\n\t|file: "<< __FILE__<<",line: " << __LINE__<<std::endl; }

	constexpr float epsilon = 1e-5f;
	constexpr float shadowEpsilon = 0.0001f;

	constexpr float pi = 3.14159265358979323846f;
	constexpr float invpi = 0.31830988618379067154f;
	constexpr float inv2pi = 0.15915494309189533577f;
	constexpr float inv4pi = 0.07957747154594766788f;
	constexpr float piover2 = 1.57079632679489661923f;
	constexpr float piover4 = 0.78539816339744830961f;
	constexpr float sqrtsquare = 1.41421356237309504880f;
	constexpr float fInfinity = std::numeric_limits<float>::max();

	class RawCamera;
	struct Light;
	class Shader;
	class TexturedModel;
	class Entity;
	class Terrain;
	class RawModel;
	class Loader;
	struct Light;
}

#endif // !SLOTH_H_
