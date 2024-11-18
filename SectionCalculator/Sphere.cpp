#include "Sphere.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Exceptions.h"

Sphere::Sphere()
{
    points = nullptr;
    pointsCount = 0;
    radius = 0.0;
}

Sphere::Sphere(Point* points, int pointsCount) : ThreeDimensionalShape(points, pointsCount)
{
    this->radius = CalculateRadius(points[0], points[1]);
    IsValid();
}

double Sphere::CalculateFrontSectionPerimeter(Point sectionPoint)
{
    double d = CalculateDistance(points[0], sectionPoint);

    if (d > radius) {
		throw SectionPointOutOfShapeException();
    }

    double intersectionRadius = std::sqrt(radius * radius - d * d);

    double perimeter = 2 * M_PI * intersectionRadius;
    return perimeter;
}

double Sphere::CalculateHorizontalSectionPerimeter(Point sectionPoint)
{
	double d = CalculateDistance(points[0], sectionPoint);

    if (d > radius) {
        throw SectionPointOutOfShapeException();
    }

    double intersectionRadius = std::sqrt(radius * radius - d * d);

    double perimeter = 2 * M_PI * intersectionRadius;
    return perimeter;
}

bool Sphere::IsValid()
{
    if (pointsCount != 2) {
		throw InvalidPointCountException();
        return false;
    }

	if (radius <= 0) {
		throw InvalidShapeException();
		return false;
	}

	if (points[0] == points[1]) {
		throw DuplicatePointsException();
		return false;
	}

    return true;
}
