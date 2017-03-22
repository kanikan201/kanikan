#include "stdafx.h"
#include "Map.h"

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
		MapChip* mapChip = NewGO<MapChip>(0);
		mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
	}
}

void Map::Update()
{
}
