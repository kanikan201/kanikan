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

//�}�b�v�𐶐�����֐�
//����(�}�b�v�f�[�^,�I�u�W�F�N�g��)
void Map::Create(SMapInfo* mapLocInfo, int numObject)
{
	//�u����Ă���I�u�W�F�N�g�̐��̃}�b�v�`�b�v�𐶐�
	for (int i = 0; i < numObject; i++) {
		MapChip* mapChip = NewGO<MapChip>(0);
		mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
	}
}

void Map::Update()
{
}
