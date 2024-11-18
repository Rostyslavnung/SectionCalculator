#include "pch.h"
#include "CppUnitTest.h"
#include "../SectionCalculator/Point.h"
#include "../SectionCalculator/Pyramid.h"
#include "../SectionCalculator/Sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../SectionCalculator/Exceptions.h"
#include "../SectionCalculator/Functions.h"
#include <iostream>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SCTest
{
	TEST_CLASS(SCTest)
	{
	public:

		TEST_METHOD(PointConstructorTest)
		{
			Point pnt = Point();
			Assert::AreEqual(0.0, pnt.GetX());
			Assert::AreEqual(0.0, pnt.GetY());
			Assert::AreEqual(0.0, pnt.GetZ());
			Point point(1, 2, 3);
			Assert::AreEqual(1.0, point.GetX());
			Assert::AreEqual(2.0, point.GetY());
			Assert::AreEqual(3.0, point.GetZ());
		}

		TEST_METHOD(PointSettersTest)
		{
			Point point(1, 2, 3);
			point.SetX(4);
			point.SetY(5);
			point.SetZ(6);
			Assert::AreEqual(4.0, point.GetX());
			Assert::AreEqual(5.0, point.GetY());
			Assert::AreEqual(6.0, point.GetZ());
		}

		TEST_METHOD(PointEqualityTest)
		{
			Point point1(1, 2, 3);
			Point point2(1, 2, 3);
			Assert::IsTrue(point1 == point2);
			Point point3(4, 5, 6);
			Assert::IsFalse(point1 == point3);
		}

		TEST_METHOD(PyramidConstructorsTest)
		{
			
			Point* points = new Point[4];
			points[0] = Point(0, 0, 0);
			points[1] = Point(1, 0, 0);
			points[2] = Point(1, 1, 0);
			points[3] = Point(0, 1, 0);
			try {
				Pyramid pyramid2 = Pyramid(points, 4);
			}
			catch (const std::exception& e)
			{
				Assert::AreEqual("Invalid point count", e.what());
			}
			delete[] points;
			Point* points2 = new Point[5];
			points2[0] = Point(0, 0, 0);
			points2[1] = Point(1, 0, 0);
			points2[2] = Point(1, 1, 0);
			points2[3] = Point(0, 1, 0);
			points2[4] = Point(0.5, 0.5, 1);
			Pyramid pyramid3 = Pyramid(points2, 5);
			Assert::IsTrue(pyramid3.IsValid());
			Assert::AreEqual(5, pyramid3.GetPointsCount());
			delete[] points2;
		}

		TEST_METHOD(CalculateDistanceTest)
		{
			Point point1(0, 0, 0);
			Point point2(1, 1, 1);
			Pyramid pyramid = Pyramid();
			Assert::AreEqual(sqrt(3.0), pyramid.CalculateDistance(point1, point2));
		}

		TEST_METHOD(PyramidGetTopPointTest)
		{
			Point* points = new Point[5];
			points[0] = Point(0, 0, 0);
			points[1] = Point(1, 0, 0);
			points[2] = Point(1, 1, 0);
			points[3] = Point(0, 1, 0);
			points[4] = Point(0.5, 0.5, 1);
			Pyramid pyramid = Pyramid(points, 5);
			Assert::IsTrue(pyramid.GetTopPoint() == Point(0.5, 0.5, 1));
			delete[] points;
		}

		TEST_METHOD(SphereConstructorsTest)
		{
			Point* points = new Point[4];
			points[0] = Point(0, 0, 0);
			points[1] = Point(1, 0, 0);
			points[2] = Point(1, 1, 0);
			points[3] = Point(0, 1, 0);
			Sphere sphere = Sphere();
			Assert::AreEqual(0, sphere.GetPointsCount());
			try {
				Sphere sphere2 = Sphere(points, 4);
			}
			catch (const std::exception& e)
			{
				Assert::AreEqual("Invalid point count", e.what());
			}
			delete[] points;
			Point* points2 = new Point[2];
			points2[0] = Point(0, 0, 0);
			points2[1] = Point(1, 1, 1);
			Sphere sphere3 = Sphere(points2, 2);
			Assert::IsTrue(sphere3.IsValid());
			Assert::AreEqual(2, sphere3.GetPointsCount());
			delete[] points2;
		}

		TEST_METHOD(SphereCalculateRadiusTest)
		{
			Point point1(0, 0, 0);
			Point point2(1, 1, 1);
			Sphere sphere = Sphere();
			Assert::AreEqual(sqrt(3.0), sphere.CalculateRadius(point1, point2));
		}

		TEST_METHOD(SphereCalculateFrontSectionPerimeterTest)
		{
			Point* points = new Point[2];
			points[0] = Point(0, 0, 0);
			points[1] = Point(1, 1, 1);
			Sphere sphere = Sphere(points, 2);
			try {
				sphere.CalculateFrontSectionPerimeter(Point(0, 0, 2));
			}
			catch (const std::exception& e)
			{
				Assert::AreEqual("Section point is out of shape", e.what());
			}
			delete[] points;
		}

		TEST_METHOD(SphereCalculateHorizontalSectionPerimeterTest)
		{
			Point* points = new Point[2];
			points[0] = Point(0, 0, 0);
			points[1] = Point(1, 1, 1);
			Sphere sphere = Sphere(points, 2);
			try {
				sphere.CalculateHorizontalSectionPerimeter(Point(0, 0, 2));
			}
			catch (const std::exception& e)
			{
				Assert::AreEqual("Section point is out of shape", e.what());
			}
			delete[] points;
		}

		TEST_METHOD(PyramidInvalidConstructionTest)
		{
			Point* points = new Point[5];
			points[0] = Point(0, 0, 0);
			points[1] = Point(1, 0, 0);
			points[2] = Point(1, 1, 0);
			points[3] = Point(0, 1, 1);
			points[4] = Point(0.5, 0.5, 2);

			try {
				Pyramid pyramid(points, 5);
			}
			catch (const BasePointsLocationException& e) {
				Assert::AreEqual("Base points do not lie in the same plane", e.what());
			}
			delete[] points;
		}

		TEST_METHOD(PyramidCalculateFrontSectionPerimeterTest)
		{
			Point* points = new Point[5];
			points[0] = Point(0, 0, 0);
			points[1] = Point(1, 0, 0);
			points[2] = Point(1, 1, 0);
			points[3] = Point(0, 1, 0);
			points[4] = Point(0.5, 0.5, 1);

			Pyramid pyramid(points, 5);
			Point sectionPoint(0.5, 0.5, 0);

			double perimeter = pyramid.CalculateFrontSectionPerimeter(sectionPoint);
			Assert::AreEqual(3.24, perimeter, 0.01);
			delete[] points;
		}

		TEST_METHOD(PyramidCalculateHorizontalSectionPerimeterTest)
		{
			Point* points = new Point[5];
			points[0] = Point(0, 0, 0);
			points[1] = Point(1, 0, 0);
			points[2] = Point(1, 1, 0);
			points[3] = Point(0, 1, 0);
			points[4] = Point(0.5, 0.5, 1);

			Pyramid pyramid(points, 5);
			Point sectionPoint(0.5, 0.5, 0.5);

			double perimeter = pyramid.CalculateHorizontalSectionPerimeter(sectionPoint);
			Assert::AreEqual(2.0, perimeter, 0.001);
			delete[] points;
		}

		TEST_METHOD(SphereConstructionTest)
		{
			Point* points = new Point[2];
			points[0] = Point(0, 0, 0);
			points[1] = Point(1, 0, 0);

			Sphere sphere(points, 2);
			Assert::IsTrue(sphere.IsValid());
			Assert::AreEqual(2, sphere.GetPointsCount());
			Assert::AreEqual(1.0, sphere.GetRadius());
			delete[] points;
		}

		TEST_METHOD(SphereInvalidConstructionTest)
		{
			Point* points = new Point[1];
			points[0] = Point(0, 0, 0);

			try {
				Sphere sphere(points, 1);
			}
			catch (const InvalidPointCountException& e) {
				Assert::AreEqual("Invalid point count", e.what());
			}
			delete[] points;
		}

		TEST_METHOD(SphereSectionPointOutOfShapeTest)
		{
			Point* points = new Point[2];
			points[0] = Point(0, 0, 0);
			points[1] = Point(0, 0, 2);

			Sphere sphere(points, 2);
			Point sectionPoint(0, 0, 3); // Точка за межами сфери

			try {
				sphere.CalculateFrontSectionPerimeter(sectionPoint);
			}
			catch (const SectionPointOutOfShapeException& e) {
				Assert::AreEqual("Section point is out of shape", e.what());
			}

			delete[] points;
		}

		TEST_METHOD(InvalidFileFormatExceptionTest) {
			try {
				ReadFile("file.doc");
			}
			catch (const InvalidFileFormatException& e) {
				Assert::AreEqual("Invalid file format", e.what());
			}
		}

		TEST_METHOD(FileNotFoundExceptionTest) {
			try {
				ReadFile("nonexistent.txt");
			}
			catch (const FileNotFoundException& e) {
				Assert::AreEqual("File not found", e.what());
			}
		}

		TEST_METHOD(EmptyPathExceptionTest) {
			try {
				ReadFile("");
			}
			catch (const EmptyPathException& e) {
				Assert::AreEqual("Path is empty", e.what());
			}
		}

		TEST_METHOD(EmptyFileExceptionTest) {
			std::ofstream file("empty.txt");
			file.close();
			try {
				ReadFile("empty.txt");
			}
			catch (const EmptyFileException& e) {
				Assert::AreEqual("Empty file", e.what());
			}
			remove("empty.txt");
		}

		TEST_METHOD(InvalidSectionTypeExceptionTest) {
			try {
				std::vector<std::string> lines = { "P4 P-x 0,0,0:1,0,0:1,1,0:0,1,0:0.5,0.5,1;0,0,2" };
				ThreeDimensionalShape* ptr = nullptr;
				ProcessFile(lines, ptr);
			}
			catch (const InvalidSectionTypeException& e) {
				Assert::AreEqual("Invalid section type", e.what());
			}
		}

		TEST_METHOD(InvalidShapeTypeExceptionTest) {
			try {
				std::vector<std::string> lines = { "Px P-h 0,0,0:1,0,0:1,1,0:0,1,0:0.5,0.5,1;0,0,2" };
				ThreeDimensionalShape* ptr = nullptr;
				ProcessFile(lines, ptr);
			}
			catch (const InvalidShapeTypeException& e) {
				Assert::AreEqual("Invalid shape type", e.what());
			}
		}

		TEST_METHOD(InvalidPointCountExceptionTest) {
			try {
				Point points[3] = { Point(0, 0, 0), Point(1, 1, 1), Point(0, 1, 1) };
				Pyramid pyramid(points, 3);
			}
			catch (const InvalidPointCountException& e) {
				Assert::AreEqual("Invalid point count", e.what());
			}
		}

		TEST_METHOD(SectionPointNotFoundExceptionTest) {
			try {
				std::vector<std::string> lines = { "P4 P-h 0,0,0:1,0,0:1,1,0:0,1,0:0.5,0.5,1" };
				ThreeDimensionalShape* ptr = nullptr;
				ProcessFile(lines, ptr);
			}
			catch (const SectionPointNotFoundException& e) {
				Assert::AreEqual("Section point not found", e.what());
			}
		}

		TEST_METHOD(BasePointsLocationExceptionTest) {
			try {
				Point points[5] = { Point(0, 0, 0), Point(1, 0, 0), Point(1, 1, 1), Point(0, 1, 0), Point(0.5, 0.5, 2) };
				Pyramid pyramid(points, 5);
			}
			catch (const BasePointsLocationException& e) {
				Assert::AreEqual("Base points do not lie in the same plane", e.what());
			}
		}

		TEST_METHOD(DuplicatePointsExceptionTest) {
			try {
				Point points[5] = { Point(0, 0, 0), Point(1, 0, 0), Point(1, 0, 0), Point(0, 1, 0), Point(0.5, 0.5, 1) };
				Pyramid pyramid(points, 5);
			}
			catch (const DuplicatePointsException& e) {
				Assert::AreEqual("Duplicate points", e.what());
			}
		}

		TEST_METHOD(SectionPointOutOfShapeExceptionTest) {
			try {
				Point points[5] = { Point(0, 0, 0), Point(1, 0, 0), Point(1, 1, 0), Point(0, 1, 0), Point(0.5, 0.5, 1) };
				Pyramid pyramid(points, 5);
				pyramid.CalculateFrontSectionPerimeter(Point(0, 0, 2));
			}
			catch (const SectionPointOutOfShapeException& e) {
				Assert::AreEqual("Section point is out of shape", e.what());
			}
		}

		TEST_METHOD(InvalidShapeExceptionTest) {
			try {
				Point points[2] = { Point(0, 0, 0), Point(0, 0, 0) };
				Sphere sphere(points, 2);
			}
			catch (const InvalidShapeException& e) {
				Assert::AreEqual("Invalid shape", e.what());
			}
		}

		TEST_METHOD(NonCoplanarBaseExceptionTest)
		{
			try {
				Point* points = new Point[5];
				points[0] = Point(0, 0, 0);
				points[1] = Point(1, 0, 1);
				points[2] = Point(1, 1, 1);
				points[3] = Point(0, 1, 1);
				points[4] = Point(0.5, 0.5, 2);
				Pyramid pyramid = Pyramid(points, 5);
			}
			catch (const std::exception& e) {
				Assert::AreEqual("Base points do not lie in the same plane", e.what());
			}
		}
	};
}
