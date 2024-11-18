#pragma once
#include "ThreeDimensionalShape.h"
#include "Point.h"
class Sphere : public ThreeDimensionalShape
{
private:
	double radius;
public:
	Sphere();
	Sphere(Point* points, int pointsCount);
	double CalculateFrontSectionPerimeter(Point point) override;
	double CalculateHorizontalSectionPerimeter(Point point) override;
	inline double CalculateRadius(Point point1, Point point2) { return CalculateDistance(point1, point2); }
	inline double GetRadius() { return radius; }
	bool IsValid()  override;
};

