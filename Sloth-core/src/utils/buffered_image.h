#pragma once
#ifndef SLOTH_BUFFERED_IMAGE_H_
#define SLOTH_BUFFERED_IMAGE_H_

#include <sloth.h>

namespace sloth {

	// 数据从左上至右下，RGB 图片依次为 R,G,B，每个元素占一个字节
	class BufferedImage
	{
	private:
		unsigned char *m_ImageData;
		int m_Width;
		int m_Height;
		int m_Channel;

	public:
		BufferedImage(std::string imagePath);
		~BufferedImage();

		inline unsigned char getR(int x, int y) {
			return m_ImageData[m_Width * m_Channel * y + x * m_Channel];
		}

		inline unsigned char getG(int x, int y) {
			return m_ImageData[m_Width * m_Channel * y + x * m_Channel + 1];
		}
		
		inline unsigned char getB(int x, int y) {
			return m_ImageData[m_Width * m_Channel * y + x * m_Channel + 2];
		}

		inline unsigned char getA(int x, int y) {
			return m_ImageData[m_Width * m_Channel * y + x * m_Channel + 3];
		}

		inline int getRGB(int x, int y)
		{
			int first_pos = m_Width * m_Channel * y + x * m_Channel;
			int i = static_cast<int>(m_ImageData[first_pos]) << 16 |
				static_cast<int>(m_ImageData[first_pos + 1]) << 8 |
				static_cast<int>(m_ImageData[first_pos + 2]) | 0xff000000;
			return i;
		}

		inline int getWidth() { return m_Width; }
		inline int getHeight() { return m_Height; }
		inline int getChannel() { return m_Channel; }
	};

}

#endif // !SLOTH_BUFFERED_IMAGE_H_
