#include "stdafx.h"
#include "RouteJudge.h"
#include "scene/GameScene.h"
#include "RouteObject.h"
#include "Map/Block.h"
#include "../Rock.h"

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
	RouteCount = 0;
	int warpCount = 0;

	for (int i = 0; i < Width; i++) {
		for (int j = 0; j < Height; j++) {
			int tmp = map[j][i];
			//何もないor柱
			if (tmp == Empty || tmp == Pole || tmp == Dummy 
				|| tmp == Block1 || tmp == Block2 || tmp == Return) {
				StageCount++;
			}

			if (tmp == Trap1) {
				routeObject[j][i]->SetTrap();
			}

			//ワープトラップ
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

	//プレイヤーの初期位置を通ったマスにする
	map[set_y][set_x] = Path;
	routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
	routeObject[currentGrid.y][currentGrid.x]->Perticle();

	InitroutePos = false;
	RouteCount++;

	isReset = false;
	ResetEnd = false;

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
			if (StageCount - RouteCount <= 1) {
				isChange = true;
				Change();
				se->Init("Assets/sound/kira2.wav");
				se->Play(false);
				ResetEnd = true;
			}
			else {
				g_gameScene->getPlayer()->KneelDownAnimation();
				//ゲームオーバー処理
				g_gameScene->SetGameOver();
			}
			break;

		//ワープパネル
		case WarpTrap:
			if (ResetEnd==true) {
				Warp();
				RouteCount++;
				se->Init("Assets/sound/warp.wav");
				se->Play(false);
			}
			else {
				g_gameScene->getPlayer()->KneelDownAnimation();
				//ゲームオーバー処理
				g_gameScene->SetGameOver();
			}
			break;
		//ブロックのあるマス
		case Block1:
			map[currentGrid.y][currentGrid.x] = Path;
			//通ったマスを描画する
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			RouteCount++;

			se->Init("Assets/sound/panel.wav");
			se->Play(false);
			
			Blockflg = true;

			break;
		case Block2:
			map[currentGrid.y][currentGrid.x] = Path;
			//通ったマスを描画する
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			RouteCount++;

			se->Init("Assets/sound/panel.wav");
			se->Play(false);

			rock[0]->SetActiveFlag(true);
			rock[1]->SetActiveFlag(true);
			Block2flg = true;

			break;
		//元に戻すマス
		case Return:
			map[currentGrid.y][currentGrid.x] = Path;
			//通ったマスを描画する
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			RouteCount++;

			se->Init("Assets/sound/panel.wav");
			se->Play(false);

			Count++;
			Returnflg = true;

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

			se->Init("Assets/sound/panel.wav");
			se->Play(false);
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