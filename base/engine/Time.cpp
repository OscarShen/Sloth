#include "Time.h"
#include <GLFW/glfw3.h>

double Time::delta = 0;

double Time::getTime() {
	return glfwGetTime();
}

double Time::getDelta() {
	return delta;
}

void Time::setDelta(double delta)
{
	Time::delta = delta;
}
