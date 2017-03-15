#include "stdafx.h"
#include "Map.h"

struct SMapInfo {
	const char*	modelName;
	CVector3	position;
	CQuaternion	rotation;
};

//マップの配置情報
SMapInfo mapLocInfo[] = {
#include "locationInfo.h"
};

Map::Map()
{
}


Map::~Map()
{
}

bool Map::Start()
{
	//マップに配置されているオブジェクト数を計算
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);

	//置かれているオブジェクトの数のマップチップを生成
	for (int i = 0; i < numObject; i++) {
			MapChip* mapChip = NewGO<MapChip>(0);
			mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
	}

	return true;
}

void Map::Update()
{

}
