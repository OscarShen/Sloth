#pragma once
#ifndef SLOTH_TILE_LAYER_H_
#define SLOTH_TILE_LAYER_H_

#include "layer.h"
#include "../batch_renderer_2d.h"

namespace sloth { namespace graphics {

	class TileLayer:public Layer
	{
	public:
		TileLayer(Shader *shader);
		~TileLayer();
		void TileLayer::render() override;
	};

} }


#endif // !SLOTH_TILE_LAYER_H_
