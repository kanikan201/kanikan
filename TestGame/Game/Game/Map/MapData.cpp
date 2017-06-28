#include "stdafx.h"
#include "MapData.h"
#include "scene/GameScene.h"

//マップ０（ステージ1）
int MapData::sMap_00[MAP_0_HEIGHT][MAP_0_WIDTH] = {
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

//マップ１（ステージ2）
int MapData::sMap_01[MAP_1_HEIGHT][MAP_1_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 3, 3, 1, 3, 3, 1 },
	{ 1, 3, 0, 0, 0, 5, 3, 1 },
	{ 1, 3, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 4, 0, 0, 1 },
	{ 1, 3, 5, 0, 0, 0, 1, 1 },
	{ 1, 3, 3, 0, 0, 0, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
};

//マップ２（ステージ3）
int MapData::sMap_02[MAP_2_HEIGHT][MAP_2_WIDTH] = {
	{ 1, 1, 1,  1,  1,  1, 1, 1,  1, 1 },
	{ 1, 1, 0,  0,  0,  0, 1, 1,  1, 1 },
	{ 1, 0, 0,  9,  0,  0, 8, 8,  1, 1 },
	{ 1, 0, 0,  0,  0,  0, 1, 8,  1, 1 },
	{ 1, 1, 0,  0,  0,  0, 0, 0,  1, 1 },
	{ 1, 0, 0,  0,  0,  0, 0, 0,  1, 1 },
	{ 1, 0, 0,  0,  0,  0, 1, 11, 8, 1 },
	{ 1, 0, 0,  1,  10, 0, 1, 1,  8, 1 },
	{ 1, 0, 0,  0,  0,  0, 8, 8,  8, 1 },
	{ 1, 1, 1,  1,  1,  1, 1, 1,  1, 1 },
};

//マップ情報の取得
int MapData::GetMapInfo(int x, int y)
{
	if (g_gameScene->GetStage() == en_Stage1) {
		return sMap_00[y][x];
	}
	else if (g_gameScene->GetStage() == en_Stage2) {
		return sMap_01[y][x];
	}
	else {
		return sMap_02[y][x];
	}
};

//マップの高さ
int MapData::GetHeight()
{
	if (g_gameScene->GetStage() == en_Stage1) {
		return MAP_0_HEIGHT;
	}
	else if (g_gameScene->GetStage() == en_Stage2) {
		return MAP_1_HEIGHT;
	}
	else {
		return MAP_2_HEIGHT;
	}
};

//マップの幅
int MapData::GetWidth()
{
	if (g_gameScene->GetStage() == en_Stage1) {
		return MAP_0_WIDTH;
	}
	else if (g_gameScene->GetStage() == en_Stage2) {
		return MAP_1_WIDTH;
	}
	else {
		return MAP_2_WIDTH;
	}
}