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

//リセット
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

	//前回のグリッドを記憶
	prevGrid = currentGrid;

	//プレイヤーの位置
	CVector3 pos = g_gameScene->getPlayer()->GetPosition();

	//現在の位置を更新
	currentGrid.x = (int)(-pos.x / GRID_SIZE+ WIDTH/2.0f);
	currentGrid.y = (int)(pos.z / GRID_SIZE+ (HEIGHT-1.5f));

	//プレイヤーの初期位置を通ったマスにする
	if (Perticleflg == false) {
		routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
		routeObject[currentGrid.y][currentGrid.x]->Perticle();
		Perticleflg = true;
	}

	//マスの移動があった時
	if (prevGrid.x != currentGrid.x || prevGrid.y != currentGrid.y) {
		//通れない場所だった(壁と柱)
		if (map[currentGrid.y][currentGrid.x] == 1) {
			currentGrid = prevGrid;
		}

		//すでに通ったマスに移動
		if (map[currentGrid.y][currentGrid.x] == 5) {
			//ゲームオーバー処理
			g_gameScene->SetGameOver();
			return;
		}

		//まだ通ってない道
		if (map[currentGrid.y][currentGrid.x] == 0 || map[currentGrid.y][currentGrid.x] == 2) {
			map[currentGrid.y][currentGrid.x] = 5;
			//通ったマスを描画する
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
		}
	}
}