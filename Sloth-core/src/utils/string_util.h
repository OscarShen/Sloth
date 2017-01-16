#pragma once
#ifndef SLOTH_LOAD_STRING_H_
#define SLOTH_LOAD_STRING_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
namespace sloth { namespace util {

	std::string loadStringFromFile(const char *filepath);

} }



#endif // !SLOTH_LOAD_STRING_H_
