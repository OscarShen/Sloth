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
#include "post_processing.h"
#include <shader/shader.h>
#include <buffers/frame_buffer.h>
#include <shader/uniform.h>
#include <memory>
namespace sloth { namespace graphics {

	class ConstrastShader;
	class Constrast : public PostProcessing
	{
	public:
		Constrast(Loader &loader) :PostProcessing(loader) {}

		virtual void doPostProcessing(unsigned int colorTexture) override;

		virtual void start() override;

		virtual void end() override;
	};

#define CONSTRAST_VERTEX_FILE "src/graphics/postProcessing/contrast.vert"
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
