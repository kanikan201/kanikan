#include "stdafx.h"
#include "RouteJudge.h"
#include "Map\MapDate.h"
#include "scene/GameScene.h"


RouteJudge::RouteJudge()
{
}


RouteJudge::~RouteJudge()
{
}

bool RouteJudge::Start()
{
	currentGrid.x = 0;
	currentGrid.y = 0;

	return true;
}

void RouteJudge::Update()
{
	//�O��̃O���b�h���L��
	prevGrid = currentGrid;

	//�v���C���[�̈ʒu
	CVector3 pos = g_gameScene->getPlayer()->GetPosition();

	//���݂̈ʒu���X�V
	currentGrid.x = (int)(pos.x / GRID_SIZE);
	currentGrid.y = (int)(pos.y / GRID_SIZE);

	//�}�X�̈ړ�����������
	if (prevGrid.x != currentGrid.x || prevGrid.y != currentGrid.y) {
		//�ʂ�Ȃ��ꏊ������(�ǂƒ�)
		if (sMap[currentGrid.y][currentGrid.x] == 1 || sMap[currentGrid.y][currentGrid.x] == 2) {
			currentGrid = prevGrid;
		}

		//���łɒʂ����}�X�Ɉړ�
		if (sMap[currentGrid.y][currentGrid.x] == 5) {
			//�Ȃ񂩏���
		}
	}

	//�܂��ʂ��ĂȂ���
	if (sMap[currentGrid.y][currentGrid.x] == 0) {
		sMap[currentGrid.y][currentGrid.x] = 5;
	}
}