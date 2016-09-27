#pragma once
#include "RiverPoint.h"
#include "Definicje.h"
#include <vector>
#include <cmath>

class RiverPath
{
	std::vector<RiverPoint*> OpenList;
	std::vector<RiverPoint*> ClosedList;
	std::vector<std::vector<RiverPoint*>> Points;
	std::vector<RiverPoint*> Path;
	float TargetHeight;
	int TargetX, TargetZ;
public:
	RiverPath();
	void FindPath(int startX, int startZ, int targetX, int targetZ, float terrain[terrain_size][terrain_size], float height_Start, float height_Target);
	std::vector<RiverPoint*> GetPath(float Height_MIN);
	RiverPoint* OpenList_TakeFirst();
	void OpenList_Add(RiverPoint* item);
	void OpenList_PossibleReorder(RiverPoint * foundPoint, RiverPoint* currentPoint);
	~RiverPath();
};

 