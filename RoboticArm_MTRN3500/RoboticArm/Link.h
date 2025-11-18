#pragma once
#include "Line.h"

class Link : public Line
{
	double HubRadius;
public:
	Link() = default;
	Link(Point p, double length, double orientation, double hubRadius, int r, int g, int b);

	void Draw(HDC h);
	virtual ~Link() {};
};