#pragma once
#ifndef SLOTH_ERROR_CHECK_H_
#define SLOTH_ERROR_CHECK_H_

#include <sloth.h>
namespace sloth {

		GLenum slothCheckError(const char *file, int line);

#define glCheckError() sloth::slothCheckError(__FILE__, __LINE__)
	
}
#endif // !SLOTH_ERROR_CHECK_H_
