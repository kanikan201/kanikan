#include "stdafx.h"
#include "MapData.h"
#include "scene/GameScene.h"

//�}�b�v�O�i�X�e�[�W1�j
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

//�}�b�v�P�i�X�e�[�W2�j
int MapData::sMap_01[MAP_1_HEIGHT][MAP_1_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 5, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 5, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
};

//�}�b�v�Q�i�X�e�[�W3�j
int MapData::sMap_02[MAP_2_HEIGHT][MAP_2_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 8, 8, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 8, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 8, 1 },
	{ 1, 0, 0, 1, 0, 0, 1, 1, 8, 1 },
	{ 1, 0, 0, 0, 0, 0, 8, 8, 8, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

//�}�b�v���̎擾
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

//�}�b�v�̍���
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

//�}�b�v�̕�
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