#pragma once

#include <assert.h>

class Util
{
public:
	struct Point
	{
		Point()
		{
			x = 0;
			y = 0;
		}

		Point(int x, int y)
		{
			this->x = x;
			this->y = y;
		}

		Point operator-(const Point& point)
		{
			return Point(this->x - point.x, this->y - point.y);
		}

		Point operator+(const Point& point)
		{
			return Point(this->x + point.x, this->y + point.y);
		}

		bool operator==(const Point& point)
		{
			return (this->x == point.x && this->y == point.y);
		}

		int x, y;
	};

	static unsigned int CoordinatesToIndex(unsigned int x, unsigned int y, unsigned int width);
	static unsigned int PointToIndex(Point point, unsigned int width);

	static bool VerifyArray(const int arr[], const int arrVerifier[]);
};