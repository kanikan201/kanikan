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
	currentGrid.x = 3;
	currentGrid.y = 7;

	return true;
}

void RouteJudge::Update()
{
	//�O��̃O���b�h���L��
	prevGrid = currentGrid;

	//�v���C���[�̈ʒu
	CVector3 pos = g_gameScene->getPlayer()->GetPosition();

	//���݂̈ʒu���X�V
	currentGrid.x = (int)(-pos.x / GRID_SIZE+ WIDTH/2.0f);
	currentGrid.y = (int)(pos.z / GRID_SIZE+ (HEIGHT-1.5f));

	//�}�X�̈ړ�����������
	if (prevGrid.x != currentGrid.x || prevGrid.y != currentGrid.y) {
		//�ʂ�Ȃ��ꏊ������(�ǂƒ�)
		if (sMap[currentGrid.y][currentGrid.x] == 1) {
			currentGrid = prevGrid;
		}

		//���łɒʂ����}�X�Ɉړ�
		if (sMap[currentGrid.y][currentGrid.x] == 5) {
			//�Ȃ񂩃Q�[���I�[�o�[����
			g_gameScene->getPlayer()->SetPosition({0.0f,0.0f,0.0f});
		}
	}

	//�܂��ʂ��ĂȂ���
	if (sMap[currentGrid.y][currentGrid.x] == 0) {
		sMap[currentGrid.y][currentGrid.x] = 5;
	}
}