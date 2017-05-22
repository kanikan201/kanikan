#include "stdafx.h"
#include "Map.h"
#include "Map/ClearMarker.h"
#include "Enemy/TestEnemy.h"
#include "Route/RouteObject.h"

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
	//置かれているオブジェクトの数のマップチップを生成
	for (int i = 0; i < numObject; i++) {
		if (strcmp("clearMarker", mapLocInfo[i].modelName) == 0) {
			ClearMarker* marker = NewGO<ClearMarker>(0);
			marker->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("D_Unity", mapLocInfo[i].modelName) == 0) {
			TestEnemy* enemy = NewGO<TestEnemy>(0);
			enemy->Init(mapLocInfo[i].position);
		}
		else if (strcmp("route", mapLocInfo[i].modelName) == 0) {
			int routex = (int)(-mapLocInfo[i].position.x / GRID_SIZE + WIDTH / 2.0f);
			int routey = (int)(mapLocInfo[i].position.z / GRID_SIZE + (HEIGHT - 1.5f));
			routeObject[routey][routex] = NewGO<RouteObject>(0);
			routeObject[routey][routex]->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
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
