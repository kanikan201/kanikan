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

//�����ʒu�ݒ�
void RouteJudge::Init(int set_x, int set_y) {
	initialGrid.x = set_x;
	initialGrid.y = set_y;

	Reset(set_x, set_y);
}

//���Z�b�g(�����̓v���C���[�ʒu)
void RouteJudge::Reset(int set_x,int set_y)
{
	int	Width = g_gameScene->getMapData()->GetWidth();
	int Height = g_gameScene->getMapData()->GetHeight();

	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Height; y++) {
			map[y][x] = g_gameScene->getMapData()->GetMapInfo(x, y);
		}
	}

	map[set_y][set_x] = Path;
	currentGrid.x = set_x;
	currentGrid.y = set_y;

	InitroutePos = false;
	isReset = false;

	RouteCount = 0;
	//StageCount = 0;

	StageCount = 27;
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
	if (InitroutePos == false) {
		routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
		routeObject[currentGrid.y][currentGrid.x]->Perticle();
		InitroutePos = true;
		RouteCount++;
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
			isReset = true;
		}
		//���łɒʂ����}�X�Ɉړ�
		//�܂��́A�ז��p�l��(��)
		else if (mapTmp == Path || mapTmp == Trap1) {
			//�Q�[���I�[�o�[����
			g_gameScene->SetGameOver();
		}
		//�܂��ʂ��ĂȂ���
		else{
			map[currentGrid.y][currentGrid.x] = Path;
			//�ʂ����}�X��`�悷��
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			RouteCount++;
		}
	}

	if (Pad(0).IsTrigger(enButtonStart)) {
		g_gameScene->setClear(true);
	}
	//�N���A����
	if (isPassed()) {
		
	}
}
