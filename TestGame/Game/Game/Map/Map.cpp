#include "stdafx.h"
#include "Map.h"
#include "Map/ClearMarker.h"
#include "Enemy/TestEnemy.h"

namespace {
	const int WIDTH = 7;
	const int HEIGHT = 9;
	//0は地面、1は壁、2は柱
	static int sMap[HEIGHT][WIDTH] = {
		{1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 0, 2, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 1, 2, 1, 2, 1, 1},
		{1, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1},
	};
}

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
		else {
			MapChip* mapChip = NewGO<MapChip>(0);
			mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
	}
}

void Map::Update()
{
}
