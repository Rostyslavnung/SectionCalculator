#include "Point.h"

Point::Point()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Point::Point(double x = 0.0, double y = 0.0, double z = 0.0)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

bool Point::operator==(const Point& other) const
{
	return x == other.x && y == other.y && z == other.z;
}