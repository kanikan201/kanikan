#pragma once
#include "MapChip.h"
#include "Map\MapDate.h"

struct SMapInfo {
	const char*	modelName;
	CVector3	position;
	CQuaternion	rotation;
};

class Map : public IGameObject
{
public:
	Map();
	~Map();
	bool Start();
	void Create(SMapInfo* mapLocInfo, int numObject);
	void Update();
private:
	int routeMap[HEIGHT][WIDTH];
};