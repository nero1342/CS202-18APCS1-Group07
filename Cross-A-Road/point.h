#pragma once

struct Point {
	int x, y;
	Point();
	Point(int x, int y);
	Point& operator+=(const Point& q);
	Point operator+(const Point& q);
};

