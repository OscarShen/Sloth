#include "string_util.h"

namespace sloth { namespace util {

	std::string loadStringFromFile(const char * filepath)
	{
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string str;
		try
		{
			// Open files
			std::ifstream file(filepath);
			std::stringstream stream;
			// Read file's buffer contents into stream
			stream << file.rdbuf();
			// close file handler
			file.close();
			// Convert stream into string
			str = stream.str();
		}
		catch (std::exception e)
		{
			std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
		}
		return str;
	}
} }
