#pragma once
class Point
{
private:
	double x;
	double y;
	double z;
public:
	Point();
	Point(double x, double y, double z);
	inline double GetX() const { return x; };
	inline double GetY() const { return y; };
	inline double GetZ() const { return z; };
	void SetX(double x) { this->x = x; };
	void SetY(double y) { this->y = y; };
	void SetZ(double z) { this->z = z; };

	bool operator==(const Point& other) const;
};

