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

	Reset(set_x, set_y);
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

	map[set_y][set_x] = Path;
	currentGrid.x = set_x;
	currentGrid.y = set_y;

	InitroutePos = false;
	isReset = false;

	RouteCount = 0;
	//StageCount = 0;

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
	currentGrid.x = (int)(-pos.x / GRID_SIZE+ dat_x);
	currentGrid.y = (int)(pos.z / GRID_SIZE+ dat_y);

	//プレイヤーの初期位置を通ったマスにする
	if (InitroutePos == false) {
		routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
		routeObject[currentGrid.y][currentGrid.x]->Perticle();
		InitroutePos = true;
		RouteCount++;
	}

	//マスの移動があった時
	if (prevGrid.x != currentGrid.x || prevGrid.y != currentGrid.y) {
		int mapTmp = map[currentGrid.y][currentGrid.x];

		//通れない場所だった(壁と柱)
		if (mapTmp == Wall) {
			currentGrid = prevGrid;
		}
		//リセットパネル
		else if (mapTmp == ResetTrap) {
			isReset = true;
		}
		//すでに通ったマスに移動
		//または、邪魔パネル(仮)
		else if (mapTmp == Path || mapTmp == Trap1) {
			//ゲームオーバー処理
			g_gameScene->SetGameOver();
		}
		//まだ通ってない道
		else{
			map[currentGrid.y][currentGrid.x] = Path;
			//通ったマスを描画する
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			RouteCount++;
		}
	}

	if (Pad(0).IsTrigger(enButtonStart)) {
		g_gameScene->setClear(true);
	}
	//クリア判定
	if (isPassed()) {
		
	}
}