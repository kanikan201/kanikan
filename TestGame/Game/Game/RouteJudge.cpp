#include "stdafx.h"
#include "RouteJudge.h"
#include "scene/GameScene.h"


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
		if (map[currentGrid.y][currentGrid.x] == 0) {
			map[currentGrid.y][currentGrid.x] = 5;
		}
	}
}