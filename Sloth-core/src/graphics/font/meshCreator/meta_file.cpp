#include "meta_file.h"

using namespace std;
namespace sloth {
	namespace graphics {
		sloth::graphics::MetaFile::MetaFile(const std::string & file_path)
		{
			m_AspectRatio = static_cast<double>(Input::windowWidth) / static_cast<double>(Input::windowHeight);
			openFile(file_path);
			loadPaddingData();
			loadLineSizes();
			int imageWidth = getValueOfVariable(string("scaleW"));
			loadCharacterData(imageWidth);
			close();
		}

		void sloth::graphics::MetaFile::openFile(const std::string & file_path)
		{
			m_FileStream = std::ifstream(file_path);
			if (m_FileStream.fail()) {
				std::cout << "Open failed!\n" << __FILE__ << "\t" << __LINE__ << std::endl;
				exit(-1);
			}
		}

		void sloth::graphics::MetaFile::close()
		{
			try
			{
				m_FileStream.close();
			}
			catch (std::exception e)
			{
				std::cout << "Close failed!\n" << __FILE__ << "\t" << __LINE__ << std::endl;
			}
		}

		void sloth::graphics::MetaFile::loadPaddingData()
		{
			processNextLine();
			m_Padding = getValuesOfVariable(std::string("padding"));
			m_PaddingWidth = (*m_Padding)[META_FILE_PAD_LEFT] + (*m_Padding)[META_FILE_PAD_RIGHT];
			m_PaddingHeight = (*m_Padding)[META_FILE_PAD_TOP] + (*m_Padding)[META_FILE_PAD_BOTTON];
		}

		bool sloth::graphics::MetaFile::processNextLine()
		{
			m_Values.clear();
			std::string line;

			std::getline(m_FileStream, line);
			if (!line.size())
				return false;
			std::vector<std::string> splits;
			util::split(line, std::string(META_FILE_SPLITTER), &splits);
			for (size_t i = 0; i < splits.size(); ++i) {
				std::vector<std::string> parts;
				util::split(splits[i], std::string("="), &parts);
				if (parts.size() == 2) {
					m_Values[parts[0]] = parts[1];
				}
			}
			return true;
		}

		std::shared_ptr<std::vector<int>> sloth::graphics::MetaFile::getValuesOfVariable(std::string & variable)
		{
			std::shared_ptr<std::vector<int>> values = std::make_shared<std::vector<int>>();
			auto it = m_Values.find(variable);
			if (it != m_Values.end()) {
				std::vector<std::string> s;
				util::split(it->second, std::string(META_FILE_NUMBER_SEPARATOR), &s);
				for (size_t i = 0; i < s.size(); ++i) {
					values->push_back(atoi(s[i].c_str()));
				}
			}
			return values;
		}

		int sloth::graphics::MetaFile::getValueOfVariable(std::string & variable)
		{
			auto it = m_Values.find(variable);
			if (it != m_Values.end()) {
				return atoi(it->second.c_str());
			}
			return 0;
		}

		void sloth::graphics::MetaFile::loadLineSizes()
		{
			processNextLine();
			int lineHeightPixels = getValueOfVariable(std::string("lineHeight")) - m_PaddingHeight;
			m_VerticalPerPixelSize = TEXT_LINE_HEIGHT / static_cast<double>(lineHeightPixels);
			m_HorizontalPerPixelSize = m_VerticalPerPixelSize / m_AspectRatio;
		}

		void sloth::graphics::MetaFile::loadCharacterData(int imageWidth)
		{
			// Ìø¹ýÁ½ÐÐ
			processNextLine();
			processNextLine();
			while (processNextLine()) {
				std::shared_ptr<Character> c = loadCharacter(imageWidth);
				if (c.get() != nullptr) {
					m_MetaData[c->getID()] = c;
				}
			}
		}

		std::shared_ptr<Character> sloth::graphics::MetaFile::loadCharacter(int imageSize)
		{
			int id = getValueOfVariable(string("id"));
			if (id == TEXT_SPACE_ASCII) {
				m_SpaceWidth = (getValueOfVariable(string("xadvance")) - m_PaddingWidth) * m_HorizontalPerPixelSize;
				return std::shared_ptr<Character>();
			}
			double xTex = (static_cast<double>(getValueOfVariable(string("x"))) + ((*m_Padding)[META_FILE_PAD_LEFT] - META_FILE_DESIRED_PADDING)) / imageSize;
			double yTex = (static_cast<double>(getValueOfVariable(string("y"))) + ((*m_Padding)[META_FILE_PAD_TOP] - META_FILE_DESIRED_PADDING)) / imageSize;
			int width = getValueOfVariable(string("width")) - (m_PaddingWidth - (2 * META_FILE_DESIRED_PADDING));
			int height = getValueOfVariable(string("height")) - (m_PaddingHeight - (2 * META_FILE_DESIRED_PADDING));
			double quadWidth = width * m_HorizontalPerPixelSize;
			double quadHeight = height * m_VerticalPerPixelSize;
			double xTexSize = static_cast<double>(width) / imageSize;
			double yTexSize = static_cast<double>(height) / imageSize;
			double xOff = (getValueOfVariable(string("xoffset")) + (*m_Padding)[META_FILE_PAD_LEFT] - META_FILE_DESIRED_PADDING) * m_HorizontalPerPixelSize;
			double yOff = (getValueOfVariable(string("yoffset")) + (*m_Padding)[META_FILE_PAD_TOP] - META_FILE_DESIRED_PADDING) * m_VerticalPerPixelSize;
			double xAdvance = (getValueOfVariable(string("xadvance")) - m_PaddingWidth) * m_HorizontalPerPixelSize;
			return shared_ptr<Character>(new Character(id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance));
		}
	}
}