/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  GuiShader 
 * @version 	:  v1.0.0 
 * @description :  ���ڲ��� OpenGL gui shader ����
 * @author		:  Oscar Shen 
 * @creat 		:  2017��2��8��14:09:57
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_GUI_SHADER_H_
#define SLOTH_GUI_SHADER_H_
#include "../shader/shader.h"
namespace sloth { namespace graphics {

	class GuiShader:public Shader
	{
	private:
		static GuiShader *m_Inst;

		int m_LocTransformationMatrix;

	public:
		~GuiShader(){ delete m_Inst; }
		// ����ģʽ
		static GuiShader *inst();

		void loadTransformation(glm::mat4 &matrix);

	private:
		GuiShader();

	protected:
		// ��ȡ������ GUI ��ص� uniform ������ַ��
		// �ڹ������е���һ�μ���
		virtual void getAllUniformLocation() override;
	};

} }



#endif // !SLOTH_GUI_SHADER_H_
