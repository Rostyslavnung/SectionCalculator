#include "ThreeDimensionalShape.h"
#include <cmath>

ThreeDimensionalShape::ThreeDimensionalShape()
{
	points = nullptr;
	pointsCount = 0;
}

ThreeDimensionalShape::ThreeDimensionalShape(Point* points, int pointsCount)
{
	this->pointsCount = pointsCount;
	this->points = new Point[pointsCount];
	for (int i = 0; i < pointsCount; i++)
	{
		this->points[i] = points[i];
	}
}

ThreeDimensionalShape::~ThreeDimensionalShape()
{
	delete[] points;
}

double ThreeDimensionalShape::CalculateDistance(Point point1, Point point2)
{
	double x = point2.GetX() - point1.GetX();
	double y = point2.GetY() - point1.GetY();
	double z = point2.GetZ() - point1.GetZ();
	return sqrt(x * x + y * y + z * z);
}