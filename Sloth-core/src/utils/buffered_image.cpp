#include "buffered_image.h"

namespace sloth { namespace util {
	BufferedImage::BufferedImage(std::string imagePath)
	{
		m_ImageData = SOIL_load_image(imagePath.c_str(), &m_Width, &m_Height, &m_Channel, SOIL_LOAD_AUTO);
		if (!m_ImageData) {
			// TODO! Add to log!
			printf("Buffered Image failed to initiate! \n%s, %d\n", __FILE__, __LINE__);
			exit(-1);
		}
	}

	BufferedImage::~BufferedImage()
	{
		SOIL_free_image_data(m_ImageData);
	}

} }

