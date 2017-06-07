#include "stdafx.h"
#include "Map\MapDate.h"
#include "scene/GameScene.h"

int MapData::sMap_00[MAP_0_HEIGHT][MAP_0_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 2, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 2, 1, 1, 1, 1 },
	{ 1, 0, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1 }
};

int MapData::sMap_01[MAP_1_HEIGHT][MAP_1_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 2, 0, 1 },
	{ 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 2, 1 },
	{ 1, 0, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 2, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1 }
};

int MapData::sMap_02[MAP_2_HEIGHT][MAP_2_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

int MapData::GetMapInfo(int x, int y)
{
	if (g_gameScene->GetStage() == 0) {
		return sMap_00[y][x];
	}
	else if (g_gameScene->GetStage() == 1) {
		return sMap_01[y][x];
	}
};

int MapData::GetHeight()
{
	if (g_gameScene->GetStage() == 0) {
		return MAP_0_HEIGHT;
	}
	else if (g_gameScene->GetStage() == 1) {
		return MAP_1_HEIGHT;
	}
};

int MapData::GetWidth()
{
	if (g_gameScene->GetStage() == 0) {
		return MAP_0_WIDTH;
	}
	else if (g_gameScene->GetStage() == 1) {
		return MAP_1_WIDTH;
	}
}