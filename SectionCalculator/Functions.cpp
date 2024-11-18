#include "Functions.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Exceptions.h"
#include "Pyramid.h"
#include "Sphere.h"



std::vector<std::string> ReadFile(const std::string& path)
{
	if (path.empty())
	{
		throw EmptyPathException();
	}

	if (path.find(".txt") == std::string::npos)
	{
		throw InvalidFileFormatException();
	}

	std::vector<std::string> lines;
	std::fstream File(path);

	if (!File.is_open())
	{
		throw FileNotFoundException();
	}

	std::string line;
	while (std::getline(File, line))
	{
		lines.push_back(line);
	}
	if (lines.empty())
	{
		File.close();
		throw EmptyFileException();
	}
	File.close();
	return lines;
}

std::string BuildOutputString(const std::string shapeType, std::string intersectionType, double result)
{
	std::string output;
	std::string intersection;
	std::string shape;
	if (intersectionType == "P-h")
	{
		intersection = "горизонтального";
	}
	else if (intersectionType == "P-f")
	{
		intersection = "фронтального";
	}
	if (shapeType == "P4")
	{
		shape = "4-ної піраміди";
	}
	else if (shapeType == "P5")
	{
		shape = "5-ної піраміди";
	}
	else if (shapeType == "Sp")
	{
		shape = "сфери";
	}
	output = "Периметр " + intersection + " розрізу " + shape + " = " + std::to_string(result) + " см.";

	return output;
}

Point* VectorToArray(std::vector<Point> points, int size)
{
	Point* arr = new Point[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = points[i];
	}
	return arr;
}

std::vector<std::string> ProcessFile(const std::vector<std::string>& lines, ThreeDimensionalShape* ptr) {
	std::vector<std::string> results;
	for (const std::string& line : lines) {
		try {
			if (line.empty()) {
				throw EmptyLineException();
			}
			std::istringstream ss(line);
			std::string ShapeType, IntersectionType;
			std::vector<Point> points;
			Point sectionPoint;
			int pointsCount = 0;
			double result = 0.0;

			ss >> ShapeType >> IntersectionType;

			char delimiter = ',';
			std::string pointStr;
			while (ss.peek() != ';' && ss.peek() != '!') {
				double x = 0, y = 0, z = 0;
				Point p;

				if (!std::getline(ss, pointStr, ':')) {
					break;
				}

				std::istringstream pointStream(pointStr);
				char d;

				if (pointStream >> x >> d >> y >> d >> z) {
					p.SetX(x);
					p.SetY(y);
					p.SetZ(z);
					points.push_back(p);
				}
			}

			if (pointStr.find(';') != std::string::npos) {
				pointStr = pointStr.substr(pointStr.find(';') + 1);
				std::istringstream sectionStream(pointStr);
				double x = 0, y = 0, z = 0;
				char d;
				if (sectionStream >> x >> d >> y >> d >> z) {
					sectionPoint.SetX(x);
					sectionPoint.SetY(y);
					sectionPoint.SetZ(z);
				}
			}
			else throw SectionPointNotFoundException();

			if (ShapeType == "P4") {
				pointsCount = 5;
				if (points.size() == pointsCount) {
					Pyramid pyramid(VectorToArray(points, pointsCount), pointsCount);
					ptr = &pyramid;
					if (ptr->IsValid()) {
						if (IntersectionType == "P-h") {
							result = ptr->CalculateHorizontalSectionPerimeter(sectionPoint);
						}
						else if (IntersectionType == "P-f") {
							result = ptr->CalculateFrontSectionPerimeter(sectionPoint);
						}
						else throw InvalidSectionTypeException();
						results.push_back(BuildOutputString(ShapeType, IntersectionType, result));
					}
				}
				else throw InvalidPointCountException();
			}
			else if (ShapeType == "P5") {
				pointsCount = 6;
				if (points.size() == pointsCount) {
					Pyramid pyramid(VectorToArray(points, pointsCount), pointsCount);
					ptr = &pyramid;
					if (ptr->IsValid()) {
						if (IntersectionType == "P-h") {
							result = ptr->CalculateHorizontalSectionPerimeter(sectionPoint);
						}
						else if (IntersectionType == "P-f") {
							result = ptr->CalculateFrontSectionPerimeter(sectionPoint);
						}
						else throw InvalidSectionTypeException();
						results.push_back(BuildOutputString(ShapeType, IntersectionType, result));
					}
				}
				else throw InvalidPointCountException();
			}
			else if (ShapeType == "Sp") {
				pointsCount = 2;
				if (points.size() == pointsCount) {
					Sphere sphere(VectorToArray(points, pointsCount), pointsCount);
					ptr = &sphere;
					if (ptr->IsValid()) {
						if (IntersectionType == "P-h") {
							result = ptr->CalculateHorizontalSectionPerimeter(sectionPoint);
						}
						else if (IntersectionType == "P-f") {
							result = ptr->CalculateFrontSectionPerimeter(sectionPoint);
						}
						else throw InvalidSectionTypeException();
						results.push_back(BuildOutputString(ShapeType, IntersectionType, result));
					}
				}
				else throw InvalidPointCountException();
			}
			else throw InvalidShapeTypeException();
			std::cout << BuildOutputString(ShapeType, IntersectionType, result) << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
	return results;
}

void WriteFile(const std::vector<std::string>& lines)
{
	std::ofstream File("output.txt");
	for (const std::string& line : lines)
	{
		File << line << std::endl;
	}
	File.close();
}