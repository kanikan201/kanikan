#include "stdafx.h"
#include "Map.h"
#include "Map/ClearMarker.h"
#include "Enemy/TestEnemy.h"
#include "Route/RouteObject.h"
#include "../Scene/GameScene.h"

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

//�}�b�v�𐶐�����֐�
//����(�}�b�v�f�[�^,�I�u�W�F�N�g��)
void Map::Create(SMapInfo* mapLocInfo, int numObject)
{
	//�u����Ă���I�u�W�F�N�g�̐��̃}�b�v�`�b�v�𐶐�
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
			float datx = (float)(g_gameScene->getJudge()->GetinitialGrid_x() + 0.5f);
			float daty = (float)(g_gameScene->getJudge()->GetinitialGrid_y() + 0.5f);
			int routex = (int)(mapLocInfo[i].position.x / GRID_SIZE + datx);
			int routey = (int)(-mapLocInfo[i].position.z / GRID_SIZE + daty);
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
