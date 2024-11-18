#pragma once
#include "Point.h"

class ThreeDimensionalShape
{
protected:
	Point* points;
	int pointsCount;
public:
	ThreeDimensionalShape();
	ThreeDimensionalShape(Point* points, int pointsCount);
	~ThreeDimensionalShape();
	double CalculateDistance(Point point1, Point point2);
	inline int GetPointsCount() const { return pointsCount; }
	virtual double CalculateFrontSectionPerimeter(Point point) = 0;
	virtual double CalculateHorizontalSectionPerimeter(Point point) = 0;
	virtual bool IsValid() = 0;
};

