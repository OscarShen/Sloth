#include "text_mesh_creator.h"
#include "line.hpp"
#include "meta_file.h"
#include "gui_text.h"
#include "text_mesh_data.hpp"
namespace sloth {
	TextMeshCreator::TextMeshCreator(const std::string & filePath)
	{
		m_MetaData = std::shared_ptr<MetaFile>(new MetaFile(filePath));
	}

	std::shared_ptr<TextMeshData> TextMeshCreator::createTextMesh(std::shared_ptr<GUIText> text)
	{
		std::shared_ptr<std::vector<std::shared_ptr<Line>>> lines = createStructure(text);
		std::shared_ptr<TextMeshData> data = createQuadVertices(text, lines);
		return data;
	}

	std::shared_ptr<std::vector<std::shared_ptr<Line>>> TextMeshCreator::createStructure(std::shared_ptr<GUIText> text)
	{
		std::string &s = text->getTextString();
		std::shared_ptr<std::vector<std::shared_ptr<Line>>> lines(new std::vector<std::shared_ptr<Line>>());
		std::shared_ptr<Line> currentLine(new Line(m_MetaData->getSpaceWidth(), text->getFontSize(), text->getMaxLineSize()));
		std::shared_ptr<Word> currentWord(new Word(text->getFontSize()));
		for (size_t i = 0; i < s.size(); ++i) {
			int ascii = static_cast<int>(s[i]);
			if (ascii == TEXT_SPACE_ASCII) { // 如果为空格，则尝试将单词加入行中
				bool added = currentLine->tryToAddWord(currentWord);
				if (!added) {
					lines->push_back(currentLine);
					currentLine = std::shared_ptr<Line>(new Line(m_MetaData->getSpaceWidth(), text->getFontSize(), text->getMaxLineSize()));
					currentLine->tryToAddWord(currentWord);
				}
				currentWord = std::shared_ptr<Word>(new Word(text->getFontSize()));
				continue;
			}
			std::shared_ptr<Character> character = m_MetaData->getCharacter(ascii);
			currentWord->addCharacter(character);
		}
		// 将最后一个单词加入行中
		completeStructure(lines, currentLine, currentWord, text);
		return lines;
	}

	void TextMeshCreator::completeStructure(std::shared_ptr<std::vector<std::shared_ptr<Line>>> lines, std::shared_ptr<Line> currentLine, std::shared_ptr<Word> currentWord, std::shared_ptr<GUIText> text)
	{
		bool added = currentLine->tryToAddWord(currentWord);
		if (!added) {
			lines->push_back(currentLine);
			currentLine = std::shared_ptr<Line>(new Line(m_MetaData->getSpaceWidth(), text->getFontSize(), text->getMaxLineSize()));
			currentLine->tryToAddWord(currentWord);
		}
		lines->push_back(currentLine);
	}

	std::shared_ptr<TextMeshData> TextMeshCreator::createQuadVertices(std::shared_ptr<GUIText> text, std::shared_ptr<std::vector<std::shared_ptr<Line>>> lines)
	{
		text->setNumberOfLines(lines->size());
		double curserX = 0.0;
		double curserY = 0.0;
		std::shared_ptr<std::vector<float>> vertices(new std::vector<float>());
		std::shared_ptr<std::vector<float>> textureCoords(new std::vector<float>());
		for (auto &line : *lines) {
			if (text->isCentered()) {
				curserX = (line->getMaxLength() - line->getLineLength()) / 2;
			}
			for (auto &word : *(line->getWords())) {
				for (auto &letter : *(word->getCharacters())) {
					addVerticesForCharacter(curserX, curserY, letter, text->getFontSize(), vertices);
					addTexCoords(textureCoords, letter->getXMin(), letter->getYMin(),
						letter->getXMax(), letter->getYMax());
					curserX += letter->getXAdvance() * text->getFontSize();
				}
				curserX += m_MetaData->getSpaceWidth() * text->getFontSize();
			}
			curserX = 0.0;
			curserY += TEXT_LINE_HEIGHT * text->getFontSize();
		}
		return std::shared_ptr<TextMeshData>(new TextMeshData(vertices, textureCoords));
	}

	void TextMeshCreator::addVerticesForCharacter(double cursorX, double cursorY, std::shared_ptr<Character> character, double fontSize, std::shared_ptr<std::vector<float>> vertices)
	{
		double x = cursorX + (character->getXOffset() * fontSize);
		double y = cursorY + (character->getYOffset() * fontSize);
		double maxX = x + (character->getWidth() * fontSize);
		double maxY = y + (character->getHeight() * fontSize);
		double properX = (2 * x) - 1;
		double properY = (-2 * y) - 1;
		double properMaxX = (2 * maxX) - 1;
		double properMaxY = (-2 * maxY) - 1;
		addVertices(vertices, properX, properY, properMaxX, properMaxY);
	}

	void TextMeshCreator::addVertices(std::shared_ptr<std::vector<float>> vertices, double x, double y, double maxX, double maxY)
	{
		vertices->push_back(static_cast<float>(x));
		vertices->push_back(static_cast<float>(y));
		vertices->push_back(static_cast<float>(x));
		vertices->push_back(static_cast<float>(maxY));
		vertices->push_back(static_cast<float>(maxX));
		vertices->push_back(static_cast<float>(maxY));
		vertices->push_back(static_cast<float>(maxX));
		vertices->push_back(static_cast<float>(maxY));
		vertices->push_back(static_cast<float>(maxX));
		vertices->push_back(static_cast<float>(y));
		vertices->push_back(static_cast<float>(x));
		vertices->push_back(static_cast<float>(y));
	}

	void TextMeshCreator::addTexCoords(std::shared_ptr<std::vector<float>> texCoords, double x, double y, double maxX, double maxY)
	{
		texCoords->push_back(static_cast<float>(x));
		texCoords->push_back(static_cast<float>(y));
		texCoords->push_back(static_cast<float>(x));
		texCoords->push_back(static_cast<float>(maxY));
		texCoords->push_back(static_cast<float>(maxX));
		texCoords->push_back(static_cast<float>(maxY));
		texCoords->push_back(static_cast<float>(maxX));
		texCoords->push_back(static_cast<float>(maxY));
		texCoords->push_back(static_cast<float>(maxX));
		texCoords->push_back(static_cast<float>(y));
		texCoords->push_back(static_cast<float>(x));
		texCoords->push_back(static_cast<float>(y));
	}


} 

