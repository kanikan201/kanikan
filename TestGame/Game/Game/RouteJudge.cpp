#include "stdafx.h"
#include "RouteJudge.h"
#include "Map\MapDate.h"
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

	return true;
}

void RouteJudge::Update()
{
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
		if (sMap[currentGrid.y][currentGrid.x] == 1) {
			currentGrid = prevGrid;
		}

		//すでに通ったマスに移動
		if (sMap[currentGrid.y][currentGrid.x] == 5) {
			//なんかゲームオーバー処理
			g_gameScene->getPlayer()->SetPosition({0.0f,0.0f,0.0f});
		}
	}

	//まだ通ってない道
	if (sMap[currentGrid.y][currentGrid.x] == 0) {
		sMap[currentGrid.y][currentGrid.x] = 5;
	}
}