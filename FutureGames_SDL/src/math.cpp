#include "math.h"
float sign(float a) {
	return a > 0.f ? 1.f : -1.f; 
}

float clamp(float a, float min, float max)
{

	if (a < min)
	{
		return min;
	}
	if (a > max)
	{
		return max;
	}
	else return a;

	return a < min ? min : (a > max ? max : a);
}