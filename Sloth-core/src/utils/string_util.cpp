#include "string_util.h"

namespace sloth {

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
	void split(std::string & s, std::string & delim, std::vector<std::string>* ret)
	{
		size_t last = 0;
		size_t index = s.find_first_of(delim, last);
		while (index != std::string::npos)
		{
			ret->push_back(s.substr(last, index - last));
			last = index + 1;
			index = s.find_first_of(delim, last);
		}
		if (index - last > 0)
		{
			ret->push_back(s.substr(last, index - last));
		}
	}
} 
