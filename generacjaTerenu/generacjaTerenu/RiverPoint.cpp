#include "RiverPoint.h"



RiverPoint::RiverPoint()
{
	closed = false;
	opened = false;
}

RiverPoint::RiverPoint(int _x, int _z,float _height)
{
	x = _x;
	z = _z;
	height = _height;
	closed = false;
	opened = false;
}


RiverPoint::RiverPoint(RiverPoint * _parent, int _x, int _z, float _height)
{
	parent = _parent;
	x = _x;
	z = _z;
	height = _height;
}

int RiverPoint::Get_X()
{
	return x;
}

int RiverPoint::Get_Z()
{
	return z;
}

float RiverPoint::Get_Height()
{
	return height;
}

void RiverPoint::Set_Height(float _height)
{
	height = _height;
}

void RiverPoint::Set_X(int _x)
{
	x = _x;
}

void RiverPoint::Set_Z(int _z)
{
	z = _z;
}

float RiverPoint::Get_Fcost()
{
	return Fcost;
}

float RiverPoint::Get_Gcost()
{
	return Gcost;
}

float RiverPoint::Get_Hcost()
{
	return Hcost;
}

void RiverPoint::Set_Gcost(float _Gcost)
{
	Gcost = _Gcost;
	Fcost = Hcost + Gcost;
}

void RiverPoint::Set_Hcost(float _Hcost)
{
	Hcost = _Hcost;
	Fcost = Hcost + Gcost;
}

void RiverPoint::Set_Costs(float _Gcost, float _Hcost)
{
	this->Gcost = _Gcost;
	this->Hcost = _Hcost;
	this->Fcost = Gcost + Hcost;
}

void RiverPoint::Set_Parent(RiverPoint * p)
{
	this->parent = p;
}

RiverPoint * RiverPoint::Get_Parent()
{
	return this->parent;
}

bool RiverPoint::isOpen()
{
	return this->opened;
}

bool RiverPoint::isClosed()
{
	return this->closed;
}

void RiverPoint::SetOpen(bool _state)
{
	this->opened = _state;
}
void RiverPoint::SetClosed()
{
	this->closed = true;
}

bool RiverPoint::isOnPath()
{
	return this->OnPath;
}

void RiverPoint::setOnPath()
{
	this->OnPath = true;
}

bool RiverPoint::isOnOuter()
{
	return this->OnPathEgde;
}

void RiverPoint::setOnOuter()
{
	this->OnPathEgde = true;
}


RiverPoint::~RiverPoint()
{
}
