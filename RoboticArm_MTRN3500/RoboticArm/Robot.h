#pragma once
#include "Point.h"
#include "Link.h"
#include <vector>
#include <fstream>

struct LinkProperties
{
	double LinkLength;
	double Angle;
	double HubRad;
	int Red;
	int Green;
	int Blue;
};

class Robot
{
	Point Base;
	std::vector<Link*> LinkPtrs;
public:
	Robot() = default;
	Robot(Point base, std::vector<LinkProperties> data);
	void Draw(HDC h);
	void Move(std::vector<double> delta_angles);
	~Robot();
	friend std::ostream& operator<<(std::ostream& os, const Robot& r);
};