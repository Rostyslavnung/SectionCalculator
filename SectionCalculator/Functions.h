#pragma once
#include <vector>
#include <string>
#include "ThreeDimensionalShape.h"
#include "Point.h"


std::vector<std::string> ReadFile(const std::string& path);
std::string BuildOutputString(const std::string shapeType, std::string intersectionType, double result);
Point* VectorToArray(std::vector<Point> points, int size);
std::vector<std::string> ProcessFile(const std::vector<std::string>& lines, ThreeDimensionalShape* ptr);
void WriteFile(const std::vector<std::string>& lines);
