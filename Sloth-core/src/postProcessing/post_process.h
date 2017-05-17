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
#include <sloth.h>
#include "image_renderer.h"
#include <shader/shader.h>
#include <buffers/frame_buffer.h>
#include <shader/uniform.h>
#include <memory>
#include <info/info.h>
namespace sloth { 

	// 后处理：对比度
#define CONSTRAST_VERTEX_FILE "src/postProcessing/common.vert"
#define CONSTRAST_FRAGMENT_FILE "src/postProcessing/constrast.frag"
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
#define HORIZONTAL_BLUR_VERTEX_FILE "src/postProcessing/horizontal.vert"
#define HORIZONTAL_BLUR_FRAGMENT_FILE "src/postProcessing/gaussian.frag"
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
#define VERTICAL_BLUR_VERTEX_FILE "src/postProcessing/vertical.vert"
#define VERTICAL_BLUR_FRAGMENT_FILE "src/postProcessing/gaussian.frag"
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

	// 亮度滤波器
#define LUMINANCE_FILTER_VERTEX_FILE "src/postProcessing/common.vert"
#define LUMINANCE_FILTER_FRAGMENT_FILE "src/postProcessing/luminance_filter.frag"
	class LuminanceFilterShader : public Shader
	{
	public:
		UniformFloat thresHold = UniformFloat("thresHold");

		static std::shared_ptr<LuminanceFilterShader> inst() {
			static std::shared_ptr<LuminanceFilterShader> shader = nullptr;
			if (shader == nullptr) {
				shader = std::shared_ptr<LuminanceFilterShader>(new LuminanceFilterShader());
			}
			return shader;
		}

	private:
		LuminanceFilterShader() : Shader(LUMINANCE_FILTER_VERTEX_FILE, LUMINANCE_FILTER_FRAGMENT_FILE) {
			storeAllUniformLocation(std::vector<Uniform*>{&thresHold});
		}
	};
	class LuminanceFilter : public ImageRenderer
	{
	public:
		LuminanceFilter() {}
		LuminanceFilter(int width,int height) :ImageRenderer(width, height) {}

		void process(unsigned int colorTexture, float thresHold);
	};

	// 将高亮纹理的RGB颜色乘上一个系数加到原始纹理中
#define COMBINE_FILTER_VERTEX_FILE "src/postProcessing/common.vert"
#define COMBINE_FILTER_FRAGMENT_FILE "src/postProcessing/combine_filter.frag"
	class CombineFilterShader : public Shader
	{
	public:
		UniformFloat scale = UniformFloat("scale");

	private:
		UniformSampler colorTexture = UniformSampler("colorTexture");
		UniformSampler highlightTexture = UniformSampler("highlightTexture");

	public:
		static std::shared_ptr<CombineFilterShader> inst() {
			static std::shared_ptr<CombineFilterShader> shader = nullptr;
			if (shader == nullptr)
				shader = std::shared_ptr<CombineFilterShader>(new CombineFilterShader());
			return shader;
		}

	private:
		CombineFilterShader() : Shader(COMBINE_FILTER_VERTEX_FILE, COMBINE_FILTER_FRAGMENT_FILE) {
			storeAllUniformLocation(std::vector<Uniform *>{ &scale, &colorTexture, &highlightTexture });
			connectTextureUnits();
		}

		void connectTextureUnits() {
			colorTexture.loadTexUnit(0);
			highlightTexture.loadTexUnit(1);
		}
	};
	class CombineFilter : public ImageRenderer
	{
	public:
		CombineFilter() {}
		CombineFilter(int width, int height) :ImageRenderer(width, height) {}

		void process(unsigned int colorTexture, unsigned int highlightTexture, float scale);
	};
} 

#endif // !SLOTH_CONSTRAST_H_
