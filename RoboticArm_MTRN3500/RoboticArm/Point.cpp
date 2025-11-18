#include "Point.h"

Point::Point(int x, int y)
{
	X = x;
	Y = y;
}

int Point::GetX()
{
	return X;
}

int Point::GetY()
{
	return Y;
}

void Point::SetX(int x)
{
	X = x;
}

void Point::SetY(int y)
{
	Y = y;
}

Point Point::GetPointPosition()
{
	return Point(X, Y);
}