#pragma once
#ifndef SLOTH_LOAD_STRING_H_
#define SLOTH_LOAD_STRING_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
namespace sloth { namespace util {

	std::string loadStringFromFile(const char *filepath);

	void split(std::string& s, std::string& delim, std::vector<std::string>* ret);
} }



#endif // !SLOTH_LOAD_STRING_H_
