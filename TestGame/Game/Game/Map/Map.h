#pragma once
#include "MapChip.h"
class Map : public IGameObject
{
public:
	Map();
	~Map();
	bool Start();
	void Update();
};

