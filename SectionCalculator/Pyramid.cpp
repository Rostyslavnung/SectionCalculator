#include "Pyramid.h"
#include <iostream>
#include <algorithm>
#include "Exceptions.h"

Pyramid::Pyramid()
{
	points = nullptr;
	pointsCount = 0;
	topPoint = Point();
}

Pyramid::Pyramid(Point* points, int pointsCount) : ThreeDimensionalShape(points, pointsCount)
{
    if (pointsCount < 5) { throw InvalidPointCountException(); }
	this->CalculateTopPoint();
	this->CalculateBasePoints();
    IsValid();
}

Pyramid::~Pyramid()
{
	delete[] basePoints;
}

void Pyramid::CalculateTopPoint() 
{
    topPoint = points[0];
	int cnt = 0;

    for (int i = 0; i < pointsCount; i++)
    {
        if (points[i].GetZ() > topPoint.GetZ()) {
            topPoint = points[i];
            cnt++;
        }
    }
    if ((cnt == 0) && (topPoint.GetZ() <= points[1].GetZ())) {throw TopPointLocationException(); }
}

void Pyramid::CalculateBasePoints() 
{
	basePoints = new Point[pointsCount - 1];
	int basePointsCount = 0;

	for (int i = 0; i < pointsCount; i++)
	{
		if (!(points[i].GetZ() == topPoint.GetZ())) {
			basePoints[basePointsCount] = points[i];
			basePointsCount++;
		}
	}
}

double Pyramid::CalculateFrontSectionPerimeter(Point sectionPoint) {
	for (int i = 0; i < pointsCount-1; i++) {
        if (sectionPoint.GetY() < basePoints[i].GetY() && sectionPoint.GetY() < topPoint.GetY() || 
            sectionPoint.GetY() > basePoints[i].GetY() && sectionPoint.GetY() > topPoint.GetY()) {
            throw SectionPointOutOfShapeException();
        }
	}
    
    Point* intersections = new Point[pointsCount];
    int sectionPointsCount = 0;

    for (int i = 0; i < (pointsCount - 1); i++) {
        int j = (i + 1) % (pointsCount - 1);
        if ((basePoints[i].GetY() > sectionPoint.GetY() && basePoints[j].GetY() < sectionPoint.GetY()) ||
            (basePoints[i].GetY() < sectionPoint.GetY() && basePoints[j].GetY() > sectionPoint.GetY())) {
            double t = (sectionPoint.GetY() - basePoints[i].GetY()) / (basePoints[j].GetY() - basePoints[i].GetY());
            double x = basePoints[i].GetX() + t * (basePoints[j].GetX() - basePoints[i].GetX());
            double z = basePoints[i].GetZ() + t * (basePoints[j].GetZ() - basePoints[i].GetZ());
            intersections[sectionPointsCount++] = Point(x, sectionPoint.GetY(), z);
        }
    }

    for (int i = 0; i < (pointsCount - 1); i++) {
        if ((basePoints[i].GetY() > sectionPoint.GetY() && topPoint.GetY() < sectionPoint.GetY()) ||
            (basePoints[i].GetY() < sectionPoint.GetY() && topPoint.GetY() > sectionPoint.GetY())) {
            double t = (sectionPoint.GetY() - basePoints[i].GetY()) / (topPoint.GetY() - basePoints[i].GetY());
            double x = basePoints[i].GetX() + t * (topPoint.GetX() - basePoints[i].GetX());
            double z = basePoints[i].GetZ() + t * (topPoint.GetZ() - basePoints[i].GetZ());
            intersections[sectionPointsCount++] = Point(x, sectionPoint.GetY(), z);
        }
    }

    if (std::abs(sectionPoint.GetY() - topPoint.GetY()) < 1e-6) {
        intersections[sectionPointsCount++] = topPoint;
    }

    Point centroid(0, sectionPoint.GetY(), 0);
    for (int i = 0; i < sectionPointsCount; i++) {
        centroid.SetX(centroid.GetX() + intersections[i].GetX());
        centroid.SetZ(centroid.GetZ() + intersections[i].GetZ());
    }
    centroid.SetX(centroid.GetX() / sectionPointsCount);
    centroid.SetZ(centroid.GetZ() / sectionPointsCount);

    std::sort(intersections, intersections + sectionPointsCount, [&centroid](const Point& a, const Point& b) {
        double angleA = atan2(a.GetZ() - centroid.GetZ(), a.GetX() - centroid.GetX());
        double angleB = atan2(b.GetZ() - centroid.GetZ(), b.GetX() - centroid.GetX());
        return angleA < angleB;
        });

    double perimeter = 0.0;
    for (int i = 0; i < sectionPointsCount; i++) {
        perimeter += CalculateDistance(intersections[i], intersections[(i + 1) % sectionPointsCount]);
    }

    delete[] intersections;
    return perimeter;
}

double Pyramid::CalculateHorizontalSectionPerimeter(Point sectionPoint) {
    if (sectionPoint.GetZ() < basePoints[0].GetZ() || sectionPoint.GetZ() > topPoint.GetZ()) {
		throw SectionPointOutOfShapeException();
    }
    Point* intersections = new Point[pointsCount];
    int sectionPointsCount = 0;

    for (int i = 0; i < (pointsCount - 1); i++) {
        int j = (i + 1) % (pointsCount - 1);
        if ((basePoints[i].GetZ() > sectionPoint.GetZ() && basePoints[j].GetZ() < sectionPoint.GetZ()) ||
            (basePoints[i].GetZ() < sectionPoint.GetZ() && basePoints[j].GetZ() > sectionPoint.GetZ())) {
            double t = (sectionPoint.GetZ() - basePoints[i].GetZ()) / (basePoints[j].GetZ() - basePoints[i].GetZ());
            double x = basePoints[i].GetX() + t * (basePoints[j].GetX() - basePoints[i].GetX());
            double y = basePoints[i].GetY() + t * (basePoints[j].GetY() - basePoints[i].GetY());
            intersections[sectionPointsCount++] = Point(x, y, sectionPoint.GetZ());
        }
    }

    for (int i = 0; i < (pointsCount - 1); i++) {
        if ((basePoints[i].GetZ() > sectionPoint.GetZ() && topPoint.GetZ() < sectionPoint.GetZ()) ||
            (basePoints[i].GetZ() < sectionPoint.GetZ() && topPoint.GetZ() > sectionPoint.GetZ())) {
            double t = (sectionPoint.GetZ() - basePoints[i].GetZ()) / (topPoint.GetZ() - basePoints[i].GetZ());
            double x = basePoints[i].GetX() + t * (topPoint.GetX() - basePoints[i].GetX());
            double y = basePoints[i].GetY() + t * (topPoint.GetY() - basePoints[i].GetY());
            intersections[sectionPointsCount++] = Point(x, y, sectionPoint.GetZ());
        }
    }

    Point centroid(0, 0, sectionPoint.GetZ());
    for (int i = 0; i < sectionPointsCount; i++) {
        centroid.SetX(centroid.GetX() + intersections[i].GetX());
        centroid.SetY(centroid.GetY() + intersections[i].GetY());
    }
    centroid.SetX(centroid.GetX() / sectionPointsCount);
    centroid.SetY(centroid.GetY() / sectionPointsCount);

    std::sort(intersections, intersections + sectionPointsCount, [&centroid](const Point& a, const Point& b) {
        double angleA = atan2(a.GetY() - centroid.GetY(), a.GetX() - centroid.GetX());
        double angleB = atan2(b.GetY() - centroid.GetY(), b.GetX() - centroid.GetX());
        return angleA < angleB;
        });

    double perimeter = 0.0;
    for (int i = 0; i < sectionPointsCount; i++) {
        perimeter += CalculateDistance(intersections[i], intersections[(i + 1) % sectionPointsCount]);
    }

    delete[] intersections;
    return perimeter;
}

bool Pyramid::IsValid() 
{
    for (int i = 1; i < pointsCount-1; i++) {
        if (basePoints[i].GetZ() != basePoints[0].GetZ()) { throw BasePointsLocationException(); }
    }

    for (int i = 0; i < pointsCount; i++) {
        for (int j = i + 1; j < pointsCount; j++) {
            if (points[i] == points[j]) {  throw DuplicatePointsException(); }
        }
    }

    return true;
}


