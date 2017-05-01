/*
	ルート判定クラス
*/


#pragma once
#include "Map\MapDate.h"

class RouteJudge :public IGameObject
{
public:
	RouteJudge();
	~RouteJudge();
	bool Start();
	void Update();
	void Reset();

private:
	struct grid
	{
		int x;
		int y;
	};

	grid prevGrid;
	grid currentGrid;
	int map[HEIGHT][WIDTH];
};

