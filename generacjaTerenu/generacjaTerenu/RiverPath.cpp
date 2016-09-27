#include "RiverPath.h"
using namespace std;

RiverPath::RiverPath()
{
}

void RiverPath::FindPath(int startX, int startZ, int _targetX, int _targetZ, float terrain[terrain_size][terrain_size],
						 float height_Start, float height_Target)
{
	Points.resize(terrain_size, vector<RiverPoint*>(terrain_size,nullptr)); //2d vector with all Points that will be created
	RiverPoint *endPoint = nullptr,*current, *startPoint = new RiverPoint(startX, startZ, height_Start);
	TargetHeight = height_Target;
	TargetX = _targetX;
	TargetZ = _targetZ;
	OpenList.push_back(nullptr);
	OpenList.push_back(startPoint);
	Points[startX][startZ] = startPoint;
	startPoint->Set_Costs(0.0, 0.0);
	bool trigger = true;
	while (trigger)
	{
		if (OpenList.size() == 1) break; //If OpenList have no Points (first item is always null) there is no Points to check;
		current = OpenList_TakeFirst();
		for (int b = current->Get_Z() - 1; b <= current->Get_Z() + 1; b++)
			for (int a = current->Get_X() - 1; a <= current->Get_X() + 1; a++)
			{
				//	If not off the map (do this first to avoid array out-of-bounds errors)
				if (a == -1 || b == -1 || a == terrain_size || b == terrain_size) continue;
				if (Points[a][b] == nullptr)							//Point is visited first time
				{
					RiverPoint *NewPoint = new RiverPoint(current, a, b, terrain[a][b]);
					Points[a][b] = NewPoint;
					OpenList_Add(NewPoint);

					if (a == TargetX && b == TargetZ)
					{
						endPoint = NewPoint;
						trigger = false;
					}
					else
						NewPoint->SetOpen(true);
				}
				else if (Points[a][b]->isOpen() && !Points[a][b]->isClosed()) //Point was created and added to OpenList but not closed
					OpenList_PossibleReorder(Points[a][b], current);
			}
		ClosedList.push_back(current);
		current->SetClosed();
		current->SetOpen(false);
	}
	if (endPoint)
	{
		current = endPoint;
		while (true)
		{
			Path.push_back(current);
			current->setOnPath();
			current = current->Get_Parent();
			if (current == startPoint)
			{
				Path.push_back(current);
				current->setOnPath();
				break;
			}
		}
	}
		
}

vector<RiverPoint*> RiverPath::GetPath(float Height_MIN)
{
	return Path;
}

RiverPoint * RiverPath::OpenList_TakeFirst()
{
	RiverPoint *TakenFirst, *NewFirst;
	TakenFirst = OpenList[1];
	NewFirst = OpenList.back();
	OpenList.pop_back();
	if (OpenList.size() > 1)
		OpenList[1] = NewFirst;
	int u, v = 1, OpenListItemsCount = OpenList.size() - 1;
	while(true)
	{
		u = v;
		if (2 * u + 1 <= OpenListItemsCount)//if both children exist
		{
			//Check if the F cost of the parent is greater than each child.
			//Select the lowest of the two children.
			if (OpenList[u]->Get_Fcost() >= OpenList[2 * u]->Get_Fcost())
				v = 2 * u;
			if (OpenList[u]->Get_Fcost() >= OpenList[(2 * u) + 1]->Get_Fcost())
				v = 2 * u + 1;
		}
		else
		{
			if (2 * u <= OpenListItemsCount) //if only child #1 exists
			{
				//Check if the F cost of the parent is greater than child #1	
				if (OpenList[u]->Get_Fcost() >= OpenList[2 * u]->Get_Fcost())
					v = 2 * u;
			}
		}
		if (u != v) //if parent's F is > one of its children, swap them
		{
			RiverPoint *Temp = OpenList[u];
			OpenList[u] = OpenList[v];
			OpenList[v] = Temp;
		}
		else
			break; //otherwise, exit loop
	}
	return TakenFirst;
}

void RiverPath::OpenList_Add(RiverPoint * item)
{
	OpenList.push_back(item);
	int itemX = item->Get_X(),
		itemZ = item->Get_Z();
	float itemHeight = item->Get_Height();
	int parentX = item->Get_Parent()->Get_X(),
		parentZ = item->Get_Parent()->Get_Z();
	float parentHeight = item->Get_Parent()->Get_Height();
	float AddGcost, Gcost, Hcost, Fcost;

	//IMPORTANT!! CALCULATING cost from parent to new point!!! Lowering cost if new item height is smaller
	if (abs(itemX - parentX) == 1 && abs(itemZ - parentZ) == 1)
		AddGcost = ((float)((10 * sqrt(2))));// + (itemHeight - parentHeight))); //For diagonal points
	else
		AddGcost = ((float)(10) + (itemHeight - parentHeight));			 //For non-diagonal points
	Gcost = (item->Get_Parent()->Get_Gcost()) + AddGcost;
	item->Set_Gcost(Gcost);			 //Setting Gcost of the item;
	
	//IMPORTANT!! Heuristic CALCULATION of the cost to the target!!!
	Hcost = 10 * (abs(itemX - TargetX)) + (abs(itemZ - TargetZ));// +(0.1*(abs(itemHeight) + abs(TargetHeight)));
	item->Set_Hcost(Hcost);
	//IMPORTANT!! Fcost already calculated in new Point. Next step is bubble new item to right place in heap
	int m = (OpenList.size() -1);
	while (m != 1) //While item hasn't bubbled to the top (m=1)	
	{
		//Check if child's F cost is < parent's F cost. If so, swap them.	
		if (OpenList[m]->Get_Fcost() <= OpenList[m / 2]->Get_Fcost())
		{
			RiverPoint *temp = OpenList[m / 2];
			OpenList[m / 2] = OpenList[m];
			OpenList[m] = temp;
			m = m / 2;
		}
		else 
			break;
	}
}

void RiverPath::OpenList_PossibleReorder(RiverPoint * foundPoint, RiverPoint* currentPoint)
{
	int foundPoint_X = foundPoint->Get_X(),
		foundPoint_Z = foundPoint->Get_Z();
	float foundPoint_Height = foundPoint->Get_Height();
	int currentPoint_X = currentPoint->Get_X(),
		currentPoint_Z = currentPoint->Get_Z();
	float currentPoint_Height = currentPoint->Get_Height();
	float Gcost, Hcost, Fcost;

	if (abs(foundPoint_X - currentPoint_X) == 1 && abs(foundPoint_Z - currentPoint_Z))
		Gcost = ((float)((10 * sqrt(2)) + (foundPoint_Height - currentPoint_Height))); //For diagonal points
	else
		Gcost = ((float)(10) + (foundPoint_Height - currentPoint_Height));			   //For non-diagonal points
	Gcost += currentPoint->Get_Gcost();	//Possible new Gcost of foundPoint

	//If this path is shorter (G cost is lower) then change
	//the parent of cell, G cost and F cost. 		
	if (Gcost < foundPoint->Get_Gcost())
	{
		foundPoint->Set_Gcost(Gcost);
		foundPoint->Set_Parent(currentPoint);
		for (int m = 1; m < (OpenList.size()-1); m++) //look for the item in the heap
		{
			if (OpenList[m] == foundPoint)
			{
				while (m != 1) //While item hasn't bubbled to the top (m=1)	
				{
					//Check if child is < parent. If so, swap them.	
					if (OpenList[m]->Get_Fcost() < OpenList[m/2]->Get_Fcost())
					{
						RiverPoint *temp = OpenList[m / 2];
						OpenList[m / 2] = OpenList[m];
						OpenList[m] = temp;
						m = m / 2;
					}
					else
						break;
				}
			}
			break;
		}
	}
}


RiverPath::~RiverPath()
{
}
