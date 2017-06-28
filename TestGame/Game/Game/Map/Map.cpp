#include "stdafx.h"
#include "Map.h"
#include "Map/ClearMarker.h"
#include "Enemy/TestEnemy.h"
#include "Route/RouteObject.h"
#include "Scene/GameScene.h"
#include "../Block.h"
#include "Rock.h"

Map::Map()
{
}


Map::~Map()
{
}

bool Map::Start()
{
	return true;
}

//マップを生成する関数
//引数(マップデータ,オブジェクト数)
void Map::Create(SMapInfo* mapLocInfo, int numObject)
{
	int idx = 0;
	//置かれているオブジェクトの数のマップチップを生成
	for (int i = 0; i < numObject; i++) {
		if (strcmp("clearMarker", mapLocInfo[i].modelName) == 0) {
			ClearMarker* marker = NewGO<ClearMarker>(0);
			marker->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("D_Unity", mapLocInfo[i].modelName) == 0) {
			enemy = NewGO<TestEnemy>(0);
			enemy->Init(mapLocInfo[i].position);
		}
		else if (strcmp("route", mapLocInfo[i].modelName) == 0) {
			float datx = (float)(g_gameScene->getJudge()->GetInitialGrid_x() + 0.5f);
			float daty = (float)(g_gameScene->getJudge()->GetInitialGrid_y() + 0.5f);
			int routex = (int)(-mapLocInfo[i].position.x / GRID_SIZE + datx);
			int routey = (int)(mapLocInfo[i].position.z / GRID_SIZE + daty);
			routeObject[routey][routex] = NewGO<RouteObject>(0);
			routeObject[routey][routex]->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("block", mapLocInfo[i].modelName) == 0) {
			block = NewGO<Block>(0);
			block->Init(mapLocInfo[i].position,mapLocInfo[i].rotation);
		}
		else if (strcmp("Rock1", mapLocInfo[i].modelName) == 0) {
			rock[idx] = NewGO<Rock>(0);
			rock[idx]->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
			rock[idx]->SetActiveFlag(false);
			idx++;
		}
		else {
			MapChip* mapChip = NewGO<MapChip>(0);
			mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
	}
}

void Map::Update()
{
}
