/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  GuiShader 
 * @version 	:  v1.0.0 
 * @description :  用于操作 OpenGL gui shader 数据
 * @author		:  Oscar Shen 
 * @creat 		:  2017年2月8日14:09:57
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_GUI_SHADER_H_
#define SLOTH_GUI_SHADER_H_
#include "../shader/shader.h"
#include <memory>
namespace sloth { namespace graphics {

	class GuiShader:public Shader
	{
	private:
		static std::shared_ptr<GuiShader> m_Inst;

		int m_LocTransformationMatrix;

	public:
		~GuiShader(){}
		// 单例模式
		static std::shared_ptr<GuiShader> inst();

		void loadTransformation(glm::mat4 &matrix);

	private:
		GuiShader();

	protected:
		// 获取所有与 GUI 相关的 uniform 变量地址，
		// 在构造器中调用一次即可
		virtual void getAllUniformLocation() override;
	};

} }



#endif // !SLOTH_GUI_SHADER_H_
