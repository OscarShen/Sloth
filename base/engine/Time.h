#pragma once
#ifndef SLOTH_TIME_H_
#define SLOTH_TIME_H_

class Time {
public:

	static double getTime();

	static double getDelta();

	static void setDelta(double delta);

private:
	static double delta;
};

#endif // !SLOTH_TIME_H_
