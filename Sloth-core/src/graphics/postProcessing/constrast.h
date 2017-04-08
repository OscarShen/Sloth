/************************************************************************ 
 * @description :  对比度处理
 * @author		:  Oscar Shen
 * @creat 		:  2017年3月30日14:49:25
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_CONSTRAST_H_
#define SLOTH_CONSTRAST_H_
#include "image_renderer.h"
#include <shader/shader.h>
#include <buffers/frame_buffer.h>
#include <shader/uniform.h>
#include <memory>
#include <info/info.h>
namespace sloth { namespace graphics {

	class ConstrastShader;
	class Constrast : public ImageRenderer
	{
	public:
		Constrast(int width = Input::windowWidth, int height = Input::windowHeight) : ImageRenderer(width, height) {}

		void process(unsigned int colorTexture);
	};

#define CONSTRAST_VERTEX_FILE "src/graphics/postProcessing/common.vert"
#define CONSTRAST_FRAGMENT_FILE "src/graphics/postProcessing/constrast.frag"
	class ConstrastShader : public Shader
	{
	public:
		static std::shared_ptr<ConstrastShader> inst();

		UniformFloat contrast = UniformFloat("contrast");

	private:
		ConstrastShader() :Shader(CONSTRAST_VERTEX_FILE, CONSTRAST_FRAGMENT_FILE)
		{
			storeAllUniformLocation(std::vector<Uniform*>{ &contrast });
		}
	};

} }

#endif // !SLOTH_CONSTRAST_H_
