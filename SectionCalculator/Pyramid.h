#pragma once
#include "ThreeDimensionalShape.h"
#include "Point.h"
#include <iostream>

class Pyramid : public ThreeDimensionalShape
{
private:
	Point topPoint;
	Point* basePoints;
public:
	Pyramid();
	Pyramid(Point* points, int pointsCount);
	~Pyramid();
	void CalculateTopPoint();
	void CalculateBasePoints();
	inline Point GetTopPoint() const { return topPoint; }
	double CalculateFrontSectionPerimeter(Point sectionPoint) override;
	double CalculateHorizontalSectionPerimeter(Point sectionPoint) override;
	bool IsValid() override;
};

