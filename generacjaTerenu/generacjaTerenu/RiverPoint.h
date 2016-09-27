#pragma once
class RiverPoint
{
	RiverPoint *parent = 0;
	bool closed = false, opened = false;
	bool OnPath = false, OnPathEgde = false;
	int x = 0, z = 0;
	float height;
	float Fcost = 0, Gcost = 0, Hcost = 0;

public:
	RiverPoint();
	RiverPoint(int _x, int _z, float height);
	RiverPoint(RiverPoint* _parent, int _x, int _z, float height);

	int Get_X();
	int Get_Z();
	float Get_Height();
	void Set_Height(float _height);
	void Set_X(int _x);
	void Set_Z(int _z);
		
	float Get_Gcost();
	float Get_Fcost();
	float Get_Hcost();
	void Set_Gcost(float _Gcost);
	void Set_Hcost(float _Hcost);
	void Set_Costs(float _Gcost, float _Hcost);

	void Set_Parent(RiverPoint *_parent);
	RiverPoint* Get_Parent();

	bool isOpen();
	bool isClosed();
	void SetOpen(bool _state);
	void SetClosed();
	bool isOnPath();
	void setOnPath();
	bool isOnOuter();
	void setOnOuter();
	~RiverPoint();
};

