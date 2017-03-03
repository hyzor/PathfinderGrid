#include "Util.h"

unsigned int Util::CoordinatesToIndex(unsigned int x, unsigned int y, unsigned int width)
{
	return x + (y * width);
}

unsigned int Util::PointToIndex(Point point, unsigned int width)
{
	return point.x + (point.y * width);
}

bool Util::VerifyArray(const int* arr, const int* arrVerifier, const unsigned int arrSize)
{
	for (unsigned int i = 0; i < arrSize; ++i)
	{
		if (arr[i] != arrVerifier[i])
			return false;
	}

	return true;
}