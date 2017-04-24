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
	currentGrid.x = 0;
	currentGrid.y = 0;
}

void RouteJudge::Update()
{
	//前回のグリッドを記憶
	prevGrid = currentGrid;

	//プレイヤーの位置
	CVector3 pos = g_gameScene->getPlayer()->GetPosition();

	//現在の位置を更新
	currentGrid.x = (int)pos.x / GRID_SIZE;
	currentGrid.y = (int)pos.y / GRID_SIZE;

	//マスの移動があった時
	if (prevGrid.x != currentGrid.x || prevGrid.y != currentGrid.y) {
		//通れない場所だった(壁と柱)
		if (sMap[currentGrid.y][currentGrid.x] == 1 || sMap[currentGrid.y][currentGrid.x] == 2) {
			currentGrid = prevGrid;
		}

		//すでに通ったマスに移動
		if (sMap[currentGrid.y][currentGrid.x] == 5) {
			//なんか処理
		}
	}

	//まだ通ってない道
	if (sMap[currentGrid.y][currentGrid.x] == 0) {
		sMap[currentGrid.y][currentGrid.x] = 5;
	}
}