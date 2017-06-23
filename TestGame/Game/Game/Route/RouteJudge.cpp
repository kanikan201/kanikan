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

//初期位置設定
void RouteJudge::Init(int set_x, int set_y) {
	initialGrid.x = set_x;
	initialGrid.y = set_y;

	//Reset(set_x, set_y);
}

//リセット(引数はプレイヤー位置)
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
			//何もないor柱
			if (tmp == Empty || tmp == Pole) {
				StageCount++;
			}

			//ワープトラップ
			if (warpCount<2 && tmp == WarpTrap) {
				warpGrid[warpCount].x= i;
				warpGrid[warpCount].y= j;
				warpCount ++;

				routeObject[j][i]->SetWorp();
			}
			if (!isReset && tmp == ResetTrap) {
				routeObject[j][i]->SetResetLight();
			}
		}
	}

	currentGrid.x = set_x;
	currentGrid.y = set_y;

	//プレイヤーの初期位置を通ったマスにする
	map[set_y][set_x] = Path;
	routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
	routeObject[currentGrid.y][currentGrid.x]->Perticle();

	RouteCount++;

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

	//前回のグリッドを記憶
	prevGrid = currentGrid;

	//プレイヤーの位置
	CVector3 pos = g_gameScene->getPlayer()->GetPosition();

	//初期位置補正
	float dat_x = (float)initialGrid.x + 0.5f;
	float dat_y = (float)initialGrid.y + 0.5f;

	//現在の位置を更新
	currentGrid.x = (int)(-pos.x / GRID_SIZE+ dat_x);
	currentGrid.y = (int)(pos.z / GRID_SIZE+ dat_y);

	//マスの移動があった時
	if (prevGrid.x != currentGrid.x || prevGrid.y != currentGrid.y) {
		int mapTmp = map[currentGrid.y][currentGrid.x];

		CSoundSource* se = NewGO<CSoundSource>(0);

		switch (mapTmp) {
		//通れない場所だった(壁と柱)
		case Wall:
			currentGrid = prevGrid;
			break;

		//リセットパネル
		case ResetTrap:
			isReset = true;
			se->Init("Assets/sound/kira2.wav");
			se->Play(false);
			break;

		//ワープパネル
		case WarpTrap:
			Warp();
			

			se->Init("Assets/sound/warp.wav");
			se->Play(false);
			break;

		//すでに通ったマスに移動。または、邪魔パネル(仮)
		case Path:
		case Trap1:
			g_gameScene->getPlayer()->KneelDownAnimation();
			//ゲームオーバー処理
			g_gameScene->SetGameOver();
			break;

		//まだ通ってない道
		default:
			map[currentGrid.y][currentGrid.x] = Path;
			//通ったマスを描画する
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			RouteCount++;
			break;
		}
	}

	//クリア判定
	if (isPassed()) {
		g_gameScene->getPlayer()->SaluteAnimation();
		g_gameScene->setClear(true);
	}
	//デバッグ用
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

	//移動先ポジション計算
	work.x = -(warpGrid[warpNum].x - initialGrid.x)*GRID_SIZE;
	work.z = (warpGrid[warpNum].y - initialGrid.y)*GRID_SIZE;

	//プレイヤーの位置セット
	g_gameScene->getPlayer()->SetPosition(work);

	for (warpNum = 0; warpNum < 2; warpNum++) {
		map[warpGrid[warpNum].y][warpGrid[warpNum].x] = Path;
		routeObject[warpGrid[warpNum].y][warpGrid[warpNum].x]->LightReset();
	}
}