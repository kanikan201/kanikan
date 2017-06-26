#include "stdafx.h"
#include "RouteJudge.h"
#include "scene/GameScene.h"
#include "RouteObject.h"
#include "Map/Block.h"

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
	RouteCount = 0;
	int warpCount = 0;

	for (int i = 0; i < Width; i++) {
		for (int j = 0; j < Height; j++) {
			int tmp = map[j][i];
			//�����Ȃ�or��
			if (tmp == Empty || tmp == Pole || tmp == Dummy || tmp == Block1) {
				StageCount++;
			}

			if (tmp == Trap1) {
				routeObject[j][i]->SetTrap();
			}

			//���[�v�g���b�v
			if (warpCount<2 && tmp == WarpTrap) {
				warpGrid[warpCount].x= i;
				warpGrid[warpCount].y= j;
				warpCount ++;

				routeObject[j][i]->SetTrap();
			}
			if (!isReset && tmp == ResetTrap) {
				routeObject[j][i]->SetResetLight();
				StageCount++;
			}
		}
	}

	currentGrid.x = set_x;
	currentGrid.y = set_y;

	//�v���C���[�̏����ʒu��ʂ����}�X�ɂ���
	map[set_y][set_x] = Path;
	routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
	routeObject[currentGrid.y][currentGrid.x]->Perticle();

	InitroutePos = false;
	RouteCount++;

	isReset = false;

	if (isChange) {
		StageCount += CountPlus;
		isChange = false;
		Change();
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
			if (StageCount - RouteCount <= 1) {
				isChange = true;
				Change();
				se->Init("Assets/sound/kira2.wav");
				se->Play(false);
				ResetEnd = true;
			}
			else {
				g_gameScene->getPlayer()->KneelDownAnimation();
				//�Q�[���I�[�o�[����
				g_gameScene->SetGameOver();
			}
			break;

		//���[�v�p�l��
		case WarpTrap:

			if (ResetEnd==true) {
				Warp();
				RouteCount++;
				se->Init("Assets/sound/warp.wav");
				se->Play(false);
			}
			else {
				g_gameScene->getPlayer()->KneelDownAnimation();
				//�Q�[���I�[�o�[����
				g_gameScene->SetGameOver();
			}
			break;
		case Block1:
			map[currentGrid.y][currentGrid.x] = Path;
			//�ʂ����}�X��`�悷��
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			RouteCount++;

			se->Init("Assets/sound/panel.wav");
			se->Play(false);

			Blockflg = true;

			break;
		//���łɒʂ����}�X�Ɉړ��B�܂��́A�ז��p�l��(��)
		case Path:
		case Trap1:
			//g_gameScene->getPlayer()->KneelDownAnimation();
			////�Q�[���I�[�o�[����
			//g_gameScene->SetGameOver();
			break;

		//�܂��ʂ��ĂȂ���
		default:
			map[currentGrid.y][currentGrid.x] = Path;
			//�ʂ����}�X��`�悷��
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			RouteCount++;

			se->Init("Assets/sound/panel.wav");
			se->Play(false);
			break;
		}
	}

	//�N���A����
	if (isPassed()) {
		g_gameScene->getPlayer()->SaluteAnimation();
		g_gameScene->setClear(true);
	}
	//�f�o�b�O�p
	if (Pad(0).IsTrigger(enButtonStart)) {
		g_gameScene->getPlayer()->SaluteAnimation();
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

void RouteJudge::Change() 
{
	CountPlus = 0;
	int	Width = g_gameScene->getMapData()->GetWidth();
	int Height = g_gameScene->getMapData()->GetHeight();
	for (int i = 0; i < Width; i++) {
		for (int j = 0; j < Height; j++) {
			int tmp = map[j][i];
			if (tmp == Trap1) {
				map[j][i] = 0;
				routeObject[j][i]->LightReset();
				routeObject[j][i]->SetActiveFlag(false);
				CountPlus++;
			}
			if (tmp == ResetTrap) {
				map[j][i] = 0;
				routeObject[j][i]->Perticle();
				map[j][i] == Path;
				CountPlus++;
			}
			if (tmp == WarpTrap) {
				routeObject[j][i]->SetWorp();
				CountPlus++;
			}
		}
	}
	if (isChange) {
		CountPlus--;
		isReset = true;
	}
}