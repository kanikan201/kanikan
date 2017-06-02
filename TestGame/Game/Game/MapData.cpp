#include "stdafx.h"
#include "Map\MapData.h"
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

void MapData::SetMapInfo(int mapTmp, int x, int y)
{
	if (g_gameScene->isStage() == 0) {
		sMap_00[y][x] = mapTmp;
	}
	else if (g_gameScene->isStage() == 1) {
		sMap_01[y][x] = mapTmp;
	}
}

int MapData::GetMapInfo(int x, int y)
{
	if (g_gameScene->isStage() == 0) {
		return sMap_00[y][x];
	}
	else if (g_gameScene->isStage() == 1) {
		return sMap_01[y][x];
	}
};

int MapData::GetHeight()
{
	if (g_gameScene->isStage() == 0) {
		return MAP_0_HEIGHT;
	}
	else if (g_gameScene->isStage() == 1) {
		return MAP_1_HEIGHT;
	}
};

int MapData::GetWidth()
{
	if (g_gameScene->isStage() == 0) {
		return MAP_0_WIDTH;
	}
	else if (g_gameScene->isStage() == 1) {
		return MAP_1_WIDTH;
	}
}

//int MapData::GetstageCount()
//{
//	if (g_gameScene->isStage() == 0) {
//		for (int i = 0; i < MAP_0_HEIGHT; i++) {
//			for (int j = 0; j < MAP_0_WIDTH; j++) {
//				if (sMap_00[i][j] == 0 || sMap_00[i][j] == 2) {
//					stage_0_Count++;
//				}
//			}
//		}
//		return stage_0_Count;
//	}
//	else if (g_gameScene->isStage() == 1) {
//		for (int i = 0; i < MAP_1_HEIGHT; i++) {
//			for (int j = 0; j < MAP_1_WIDTH; j++) {
//				if (sMap_01[i][j] == 0 || sMap_01[i][j] == 2) {
//					stage_1_Count++;
//				}
//			}
//		}
//		return stage_1_Count;
//	}
//}