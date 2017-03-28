/************************************************************************ 
 * @description :  
 * @author		:  $username$
 * @creat 		:  $time$
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_POST_PROCESSING_H_
#define SLOTH_POST_PROCESSING_H_
#include "../engine/loader.h"
#include "../model/raw_model.hpp"
#include <map>
#include <functional>
#include <iostream>
namespace sloth { namespace graphics {

	class PostProcessing
	{
	protected:
		static RawModel quad;
		static std::vector<float> POSITIONS;

	public:
		PostProcessing(Loader &loader) {
			init(loader);
		}

		void init(Loader &loader) {
			static bool firstInit = true;
			if (firstInit) {
				quad = loader.loadToVAO(POSITIONS, 2);
				firstInit = false;
			}
		}

		virtual void doPostProcessing(unsigned int colorTexture) = 0;

	protected:
		virtual void start() {}


		virtual void end() {}
	};
} }

#endif // !SLOTH_POST_PROCESSING_H_
