#include "stdafx.h"
#include "RouteJudge.h"
#include "scene/GameScene.h"
#include "RouteObject.h"

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

	Reset();

	return true;
}

//���Z�b�g
void RouteJudge::Reset()
{
	for (int i = 0; i < HEIGHT; i++) {
		memcpy(map[i], sMap[i], sizeof(sMap[i]));
	}
	map[7][3] = 5;
	currentGrid.x = 3;
	currentGrid.y = 7;

	Perticleflg = false;
}

void RouteJudge::Update()
{
	if (g_gameScene->isStep() != GameScene::step_nomal) { return; }

	//�O��̃O���b�h���L��
	prevGrid = currentGrid;

	//�v���C���[�̈ʒu
	CVector3 pos = g_gameScene->getPlayer()->GetPosition();

	//���݂̈ʒu���X�V
	currentGrid.x = (int)(-pos.x / GRID_SIZE+ WIDTH/2.0f);
	currentGrid.y = (int)(pos.z / GRID_SIZE+ (HEIGHT-1.5f));

	//�v���C���[�̏����ʒu��ʂ����}�X�ɂ���
	if (Perticleflg == false) {
		routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
		routeObject[currentGrid.y][currentGrid.x]->Perticle();
		Perticleflg = true;
	}

	//�}�X�̈ړ�����������
	if (prevGrid.x != currentGrid.x || prevGrid.y != currentGrid.y) {
		//�ʂ�Ȃ��ꏊ������(�ǂƒ�)
		if (map[currentGrid.y][currentGrid.x] == 1) {
			currentGrid = prevGrid;
		}

		//���łɒʂ����}�X�Ɉړ�
		if (map[currentGrid.y][currentGrid.x] == 5) {
			//�Q�[���I�[�o�[����
			g_gameScene->SetGameOver();
			return;
		}

		//�܂��ʂ��ĂȂ���
		if (map[currentGrid.y][currentGrid.x] == 0 || map[currentGrid.y][currentGrid.x] == 2) {
			map[currentGrid.y][currentGrid.x] = 5;
			//�ʂ����}�X��`�悷��
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
		}
	}
}