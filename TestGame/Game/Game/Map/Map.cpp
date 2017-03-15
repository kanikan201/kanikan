#include "stdafx.h"
#include "Map.h"

struct SMapInfo {
	const char*	modelName;
	CVector3	position;
	CQuaternion	rotation;
};

//�}�b�v�̔z�u���
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
	//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);

	//�u����Ă���I�u�W�F�N�g�̐��̃}�b�v�`�b�v�𐶐�
	for (int i = 0; i < numObject; i++) {
			MapChip* mapChip = NewGO<MapChip>(0);
			mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
	}

	return true;
}

void Map::Update()
{

}
