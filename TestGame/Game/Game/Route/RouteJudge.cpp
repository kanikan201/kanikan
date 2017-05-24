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
	return true;
}

//���Z�b�g
void RouteJudge::Reset(int set_x,int set_y)
{
	for (int i = 0; i < HEIGHT; i++) {
		memcpy(map[i], sMap[i], sizeof(sMap[i]));
	}
	map[set_y][set_x] = 5;
	currentGrid.x = set_x;
	currentGrid.y = set_y;

	Perticleflg = false;
	isReset = false;

	routeCount = 0;
	stageCount = 0;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (map[i][j] == 0 || map[i][j] == 2) {
				stageCount++;
			}
		}
	}
}

void RouteJudge::Update()
{
	if (g_gameScene->isStep() != GameScene::step_nomal) { return; }

	if (isReset) {
		Reset(currentGrid.x, currentGrid.y);
		isReset = false;
	}

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
		int mapTmp = map[currentGrid.y][currentGrid.x];

		//�ʂ�Ȃ��ꏊ������(�ǂƒ�)
		if (mapTmp == 1) {
			currentGrid = prevGrid;
		}
		//���Z�b�g�p�l��(��)
		else if (mapTmp == 4) {
			isReset = true;
		}
		//���łɒʂ����}�X�Ɉړ�
		//�܂��́A�ז��p�l��(��)
		else if (mapTmp == 5|| mapTmp == 3) {
			//�Q�[���I�[�o�[����
			g_gameScene->SetGameOver();
		}
		//�܂��ʂ��ĂȂ���
		else{
			map[currentGrid.y][currentGrid.x] = 5;
			//�ʂ����}�X��`�悷��
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			routeCount++;
		}

		//�N���A����
		if (stageCount == routeCount) {
			//�Q�[���N���A����
			g_gameScene->setClear(true);
		}
	}
}