#include "Robot.h"

Robot::Robot(Point base, std::vector<LinkProperties> data) : Base(base)
{
	int n = data.size();
	LinkPtrs.resize(n);
	int i = 0;
	for (std::vector<LinkProperties>::iterator it = data.begin(); it != data.end(); it++)
	{
		LinkPtrs[i++] = new Link(Point(0, 0), it->LinkLength, it->Angle, it->HubRad, it->Red, it->Green, it->Blue);
	}
}

void Robot::Draw(HDC h)
{
	Point P;
	LinkPtrs[0]->SetStart(Base);
	LinkPtrs[0]->Draw(h);
	for (std::vector<Link*>::iterator it = LinkPtrs.begin() + 1; it != LinkPtrs.end(); it++)
	{
		P = (*(it - 1))->GetEnd();
		(*it)->SetStart(P);
		(*it)->Draw(h);
	}
}

void Robot::Move(std::vector<double> delta_angles)
{
	int i = 0;
	for (std::vector<double>::iterator it = delta_angles.begin(); it != delta_angles.end(); it++)
	{
		LinkPtrs[i++]->Move(0, 0, *it);
	}
}

Robot::~Robot()
{
	for (std::vector<Link*>::iterator it = LinkPtrs.begin(); it != LinkPtrs.end(); it++)
	{
		delete (*it);
	}
}

std::ostream& operator<<(std::ostream& os, const Robot& r)
{
	Point End_P;
	int n = r.LinkPtrs.size();
	End_P = r.LinkPtrs[n - 1]->GetEnd();
	os << End_P.GetX() << " " << End_P.GetY() << " ";
	return os;
}