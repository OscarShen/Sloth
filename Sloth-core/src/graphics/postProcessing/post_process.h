/************************************************************************ 
 * @description :  后处理类，包含多种后处理效果
 * @author		:  Oscar Shen
 * @creat 		:  2017年4月9日22:47:19
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

	// 后处理：对比度
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
	class Constrast : public ImageRenderer
	{
	public:
		Constrast() {}
		Constrast(int width, int height) : ImageRenderer(width, height) {}

		void process(unsigned int colorTexture);
	};

	// 高斯模糊
	// 水平高斯模糊
#define HORIZONTAL_BLUR_VERTEX_FILE "src/graphics/postProcessing/horizontal.vert"
#define HORIZONTAL_BLUR_FRAGMENT_FILE "src/graphics/postProcessing/gaussian.frag"
	class HorizontalBlurShader : public Shader
	{
	public:
		static std::shared_ptr<HorizontalBlurShader> inst()
		{
			static std::shared_ptr<HorizontalBlurShader> shader = nullptr;
			if (shader == nullptr)
				shader = std::shared_ptr<HorizontalBlurShader>(new HorizontalBlurShader());
			return shader;
		}

		UniformFloat targetWidth = UniformFloat("targetWidth");

	private:
		HorizontalBlurShader() :Shader(HORIZONTAL_BLUR_VERTEX_FILE, HORIZONTAL_BLUR_FRAGMENT_FILE) {
			storeAllUniformLocation(std::vector<Uniform*>{&targetWidth});
		}
	};

	class HorizontalBlur : public ImageRenderer
	{
	public:
		HorizontalBlur() {}
		HorizontalBlur(int width, int height) : ImageRenderer(width, height) {}

		void process(unsigned int colorTexture, float targetWidth);
	};

	// 垂直高斯模糊
#define VERTICAL_BLUR_VERTEX_FILE "src/graphics/postProcessing/vertical.vert"
#define VERTICAL_BLUR_FRAGMENT_FILE "src/graphics/postProcessing/gaussian.frag"
	class VerticalBlurShader : public Shader
	{
	public:
		static std::shared_ptr<VerticalBlurShader> inst() {
			static std::shared_ptr<VerticalBlurShader> shader = nullptr;
			if (shader == nullptr)
				shader = std::shared_ptr<VerticalBlurShader>(new VerticalBlurShader());
			return shader;
		}

		UniformFloat targetHeight = UniformFloat("targetHeight");

	private:
		VerticalBlurShader() :Shader(VERTICAL_BLUR_VERTEX_FILE, VERTICAL_BLUR_FRAGMENT_FILE) {
			storeAllUniformLocation(std::vector<Uniform*>{&targetHeight});
		}
	};

	class VerticalBlur : public ImageRenderer
	{
	public:
		VerticalBlur() {}
		VerticalBlur(int width, int height) : ImageRenderer(width, height) {}

		void process(unsigned int colorTexture, float targetHeight);
	};
} }

#endif // !SLOTH_CONSTRAST_H_
