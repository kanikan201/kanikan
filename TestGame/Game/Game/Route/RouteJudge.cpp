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

	//Reset(set_x, set_y);
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

	StageCount = 0;
	int warpCount = 0;

	for (int i = 0; i < Width; i++) {
		for (int j = 0; j < Height; j++) {
			int tmp = map[j][i];
			//�����Ȃ�or��
			if (tmp == Empty || tmp == Pole) {
				StageCount++;
			}

			//���[�v�g���b�v
			if (warpCount<2 && tmp == WarpTrap) {
				warpGrid[warpCount].x= i;
				warpGrid[warpCount].y= j;
				warpCount ++;

				routeObject[j][i]->SetWorp();
			}
		}
	}

	map[set_y][set_x] = Path;
	currentGrid.x = set_x;
	currentGrid.y = set_y;

	InitroutePos = false;
	isReset = false;

	RouteCount = 0;
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

		CSoundSource* se = NewGO<CSoundSource>(0);

		switch (mapTmp) {
		//�ʂ�Ȃ��ꏊ������(�ǂƒ�)
		case Wall:
			currentGrid = prevGrid;
			break;

		//���Z�b�g�p�l��
		case ResetTrap:
			isReset = true;

			se->Init("Assets/sound/kira2.wav");
			se->Play(false);
			break;

		//���[�v�p�l��
		case WarpTrap:
			Warp();
			

			se->Init("Assets/sound/warp.wav");
			se->Play(false);
			break;

		//���łɒʂ����}�X�Ɉړ��B�܂��́A�ז��p�l��(��)
		case Path:
		case Trap1:
			//�Q�[���I�[�o�[����
			g_gameScene->SetGameOver();
			break;

		//�܂��ʂ��ĂȂ���
		default:
			map[currentGrid.y][currentGrid.x] = Path;
			//�ʂ����}�X��`�悷��
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			RouteCount++;
			break;
		}
	}

	//�N���A����
	if (isPassed()) {
		g_gameScene->setClear(true);
	}
	if (Pad(0).IsTrigger(enButtonStart)) {
		g_gameScene->setClear(true);
	}
}

void RouteJudge::Warp()
{
	CVector3 work = CVector3::Zero;
	int warpNum = 0;

	if (warpGrid[warpNum].x == currentGrid.x && warpGrid[warpNum].y == currentGrid.y)
	{
		warpNum = 1;
	}

	currentGrid = warpGrid[warpNum];

	//�ړ���|�W�V�����v�Z
	work.x = -(warpGrid[warpNum].x - initialGrid.x)*GRID_SIZE;
	work.z = (warpGrid[warpNum].y - initialGrid.y)*GRID_SIZE;

	//�v���C���[�̈ʒu�Z�b�g
	g_gameScene->getPlayer()->SetPosition(work);

	for (warpNum = 0; warpNum < 2; warpNum++) {
		map[warpGrid[warpNum].y][warpGrid[warpNum].x] = Path;
		routeObject[warpGrid[warpNum].y][warpGrid[warpNum].x]->LightReset();
	}
}