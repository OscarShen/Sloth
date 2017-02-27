/************************************************************************ 
 * @project 	:  $rootnamespace$
 * @class   	:  $safeitemrootname$
 * @version 	:  v1.0.0
 * @description :  
 * @author		:  $username$
 * @creat 		:  $time$
 * @revise 		:  $time$
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_TEXT_MESH_DATA_HPP
#define SLOTH_TEXT_MESH_DATA_HPP

#include <memory>
#include <vector>

namespace sloth { namespace graphics {

	class TextMeshData
	{
	private:
		std::shared_ptr<std::vector<float>> m_VertexPositions;
		std::shared_ptr<std::vector<float>> m_TexCoords;

	public:
		TextMeshData(std::shared_ptr<std::vector<float>> vertexPositions, std::shared_ptr<std::vector<float>> texCoords)
			: m_VertexPositions(vertexPositions), m_TexCoords(texCoords) {}

		inline std::shared_ptr<std::vector<float>> getVertexPositions() const { return m_VertexPositions; }
		inline std::shared_ptr<std::vector<float>> getTexCoords() const { return m_TexCoords; }
		inline unsigned int getVertexCount() const { return m_VertexPositions->size() / 2; }
	};

	//typedef typename std::shared_ptr<TextMeshData> TextMeshData_s;
} }

#endif // !SLOTH_TEXT_MESH_DATA_HPP
