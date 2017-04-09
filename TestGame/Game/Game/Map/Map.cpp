#include "stdafx.h"
#include "Map.h"
#include "ClearMarker.h"
#include "Enemy/Enemy.h"

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
			Enemy* enemy = NewGO<Enemy>(0);
			enemy->Init(mapLocInfo[i].position);
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
