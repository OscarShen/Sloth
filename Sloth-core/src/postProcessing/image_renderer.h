/************************************************************************ 
 * @description :  
 * @author		:  $username$
 * @creat 		:  $time$
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_IMAGE_RENDERER_H_
#define SLOTH_IMAGE_RENDERER_H_
#include <sloth.h>
#include <buffers/frame_buffer.h>
#include <model/raw_model.hpp>
#include <engine/loader.h>
namespace sloth { 

	class ImageRenderer : public FrameBuffer
	{
	private:
		static RawModel quad;

	public:
		ImageRenderer() : ImageRenderer(Input::windowWidth, Input::windowHeight) {}
		ImageRenderer(int width, int height) : FrameBuffer(width, height) {
			this->addColorTextureAttachment(0);
			static bool firstInit = true;
			if (firstInit) {
				static Loader loader;
				static std::vector<float> POSITIONS { -1, 1, -1, -1, 1, 1, 1, -1 };
				std::cout << "load static position" << std::endl;
				quad = loader.loadToVAO(POSITIONS, 2);
				firstInit = false;
			}
		}
		~ImageRenderer() {}

		void renderQuad();

		unsigned int getOutputTexture() { return this->getColorTexture(0); }
	};

} 

#endif // !SLOTH_IMAGE_RENDERER_H_
