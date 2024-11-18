#pragma once
#include <exception>

class InvalidFileFormatException : public std::exception
{
public:
	InvalidFileFormatException() : std::exception("Invalid file format") {}
};

class FileNotFoundException : public std::exception
{
public:
	FileNotFoundException() : std::exception("File not found") {}
};

class EmptyPathException : public std::exception
{
public:
	EmptyPathException() : std::exception("Path is empty") {}
};

class InvalidShapeException : public std::exception
{
public:
	InvalidShapeException() : std::exception("Invalid shape") {}
};

class InvalidSectionTypeException : public std::exception
{
public:
	InvalidSectionTypeException() : std::exception("Invalid section type") {}
};

class InvalidShapeTypeException : public std::exception
{
public:
	InvalidShapeTypeException() : std::exception("Invalid shape type") {}
};

class InvalidPointCountException : public std::exception
{
public:
	InvalidPointCountException() : std::exception("Invalid point count") {}
};

class SectionPointOutOfShapeException : public std::exception
{
public:
	SectionPointOutOfShapeException() : std::exception("Section point is out of shape") {}
};

class SectionPointNotFoundException : public std::exception
{
public:
	SectionPointNotFoundException() : std::exception("Section point not found") {}
};

class BasePointsLocationException : public std::exception
{
public:
	BasePointsLocationException() : std::exception("Base points do not lie in the same plane") {}
};

class DuplicatePointsException : public std::exception
{
public:
	DuplicatePointsException() : std::exception("Duplicate points") {}
};

class EmptyLineException : public std::exception
{
public:
	EmptyLineException() : std::exception("Empty line") {}
};

class EmptyFileException : public std::exception
{
public:
	EmptyFileException() : std::exception("Empty file") {}
};

class TopPointLocationException : public std::exception
{
public:
	TopPointLocationException() : std::exception("Top point is in the same plane as base points") {}
};