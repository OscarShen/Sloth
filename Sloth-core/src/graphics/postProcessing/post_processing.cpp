#include "post_processing.h"

namespace sloth { namespace graphics {

	RawModel PostProcessing::quad = RawModel();
	std::vector<float> PostProcessing::POSITIONS = { -1,1,-1,-1,1,1,1,-1 };
} }