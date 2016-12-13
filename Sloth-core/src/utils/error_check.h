#pragma once
#ifndef SLOTH_ERROR_CHECK_H_
#define SLOTH_ERROR_CHECK_H_

#include <GL/glew.h>
#include <string>
#include <iostream>
namespace sloth {
	namespace util {

		GLenum slothCheckError(const char *file, int line);

#define glCheckError() sloth::util::slothCheckError(__FILE__, __LINE__)
	}
}
#endif // !SLOTH_ERROR_CHECK_H_
