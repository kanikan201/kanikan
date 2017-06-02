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
}

//リセット(引数はプレイヤー位置)
void RouteJudge::Reset(int set_x,int set_y)
{
	g_gameScene->getMapData()->GetMapCpy(map);
	map[set_y][set_x] = 5;
	currentGrid.x = set_x;
	currentGrid.y = set_y;

	Perticleflg = false;
	isReset = false;

	RouteCount = 0;
	StageCount = 0;

	StageCount = 27;
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
	currentGrid.x = (int)(pos.x / GRID_SIZE+ dat_x);
	currentGrid.y = (int)(-pos.z / GRID_SIZE+ dat_y);

	//プレイヤーの初期位置を通ったマスにする
	if (Perticleflg == false) {
		routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
		routeObject[currentGrid.y][currentGrid.x]->Perticle();
		Perticleflg = true;
		RouteCount++;
	}

	//マスの移動があった時
	if (prevGrid.x != currentGrid.x || prevGrid.y != currentGrid.y) {
		int mapTmp = map[currentGrid.y][currentGrid.x];

		//通れない場所だった(壁と柱)
		if (mapTmp == 1) {
			currentGrid = prevGrid;
		}
		//リセットパネル(仮)
		else if (mapTmp == 4) {
			isReset = true;
		}
		//すでに通ったマスに移動
		//または、邪魔パネル(仮)
		else if (mapTmp == 5|| mapTmp == 3) {
			//ゲームオーバー処理
			g_gameScene->SetGameOver();
		}
		//まだ通ってない道
		else{
			map[currentGrid.y][currentGrid.x] = 5;
			//通ったマスを描画する
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			RouteCount++;
		}
	}

	//クリア判定
	if (isPassed()) {
		g_gameScene->setClear(true);
	}
}