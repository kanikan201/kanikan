#include "stdafx.h"
#include "scene/GameScene.h"
#include "RouteJudge.h"
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

//�����ʒu�ݒ�(�����F�v���C���[�����ʒu�A�X�e�[�W�ԍ�)
//�V�����X�e�[�W��������Ƃ��ɌĂ�
void RouteJudge::Init(int set_x, int set_y, state_stage stg) {
	//�����ʒu�Z�b�g
	initialGrid.x = set_x;
	initialGrid.y = set_y;

	//�X�e�[�W�ԍ��Z�b�g
	stageNum = stg;

	//�X�e�[�W�̑傫�����Z�b�g
	Width	= WIDTH;
	Height	= HEIGHT;

	Reset(set_x, set_y);
}

//���Z�b�g(�����̓v���C���[�ʒu)
void RouteJudge::Reset(int set_x,int set_y)
{
	//�}�b�v�f�[�^�𕡐�
	for (int i = 0; i < Height; i++) {
		memcpy(map[i], sMap[i], sizeof(sMap[i]));
	}

	//���̈ʒu�Z�b�g
	map[set_y][set_x] = Path;
	currentGrid.x = set_x;
	currentGrid.y = set_y;

	Perticleflg = false;
	isReset		= false;

	routeCount = 0;
	stageCount = 0;

	//�p�l�����̃J�E���g
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			int tmp = map[i][j];
			if (tmp == Empty || tmp == Pole) {
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

	//�����ʒu�␳
	float dat_x = (float)initialGrid.x + 0.5f;
	float dat_y = (float)initialGrid.y + 0.5f;

	//���݂̈ʒu���X�V
	currentGrid.x = (int)(-pos.x / GRID_SIZE+ dat_x);
	currentGrid.y = (int)(pos.z / GRID_SIZE+ dat_y);

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
		if (mapTmp == Wall) {
			currentGrid = prevGrid;
		}
		//���Z�b�g�p�l��
		else if (mapTmp == ResetTrap) {
			CSoundSource* SE = NewGO<CSoundSource>(0);
			SE->Init("Assets/sound/kira2.wav");
			SE->Play(false);
			isReset = true;
		}
		//���łɒʂ����}�X�Ɉړ�
		//�܂��́A�ז��p�l��(��)
		else if (mapTmp == Path || mapTmp == 3) {
			//�Q�[���I�[�o�[����
			g_gameScene->SetGameOver();
		}
		//�܂��ʂ��ĂȂ���
		else{
			map[currentGrid.y][currentGrid.x] = Path;
			//�ʂ����}�X��`�悷��
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			routeCount++;
		}
	}
}