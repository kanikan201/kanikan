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

//リセット(引数はプレイヤー初期位置)
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
			int tmp = map[i][j];
			if (tmp == 0 || tmp == 2) {
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
		int mapTmp = map[currentGrid.y][currentGrid.x];

		//クリア判定(仮)
		//if (stageCount == routeCount && mapTmp == 6) {
		//	routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
		//	routeObject[currentGrid.y][currentGrid.x]->Perticle();
		//	//ゲームクリア処理
		//	g_gameScene->setClear(true);
		//	return;
		//}

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
			routeCount++;
		}
	}
}