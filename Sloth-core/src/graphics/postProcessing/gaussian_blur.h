/************************************************************************ 
 * @description :  高斯模糊
 * @author		:  Oscar Shen
 * @creat 		:  2017年3月30日14:49:03
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_GAUSSIAN_BLUR_H_
#define SLOTH_GAUSSIAN_BLUR_H_
#include "post_processing.h"
#include <shader/shader.h>
#include <shader/uniform.h>
#include <memory>
#include <iostream>
namespace sloth { namespace graphics {

#define HORIZONTAL_BLUR_VERTEX_FILE "src/graphics/postProcessing/horizontal.vert"
#define HORIZONTAL_BLUR_FRAGMENT_FILE "src/graphics/postProcessing/gaussian.frag"

	class HorizontalBlurShader : public Shader
	{
	public:
		static std::shared_ptr<HorizontalBlurShader> inst();

		UniformFloat targetWidth = UniformFloat("targetWidth");

	private:
		HorizontalBlurShader() :Shader(HORIZONTAL_BLUR_VERTEX_FILE, HORIZONTAL_BLUR_FRAGMENT_FILE) {
			storeAllUniformLocation(std::vector<Uniform*>{&targetWidth});
		}
	};

	class HorizontalBlur : public PostProcessing
	{
	public:
		HorizontalBlur(Loader &loader) : PostProcessing(loader) {}

		virtual void doPostProcessing(unsigned int colorTexture) override;

		virtual void start() override;

		virtual void end() override;
	};

#define VERTICAL_BLUR_VERTEX_FILE "src/graphics/postProcessing/vertical.vert"
#define VERTICAL_BLUR_FRAGMENT_FILE "src/graphics/postProcessing/gaussian.frag"

	class VerticalBlurShader : public Shader
	{
	public:
		static std::shared_ptr<VerticalBlurShader> inst();

		UniformFloat targetHeight = UniformFloat("targetHeight");

	private:
		VerticalBlurShader() :Shader(VERTICAL_BLUR_VERTEX_FILE, VERTICAL_BLUR_FRAGMENT_FILE) {
			storeAllUniformLocation(std::vector<Uniform*>{&targetHeight});
		}
	};

	class VerticalBlur : public PostProcessing
	{
	public:
		VerticalBlur(Loader &loader) : PostProcessing(loader) {}

		virtual void doPostProcessing(unsigned int colorTexture) override;

		virtual void start() override;

		virtual void end() override;
	};

} }

#endif // !SLOTH_GAUSSIAN_BLUR_H_
