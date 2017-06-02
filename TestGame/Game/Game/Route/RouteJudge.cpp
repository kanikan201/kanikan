#include "stdafx.h"
#include "scene/GameScene.h"
#include "RouteJudge.h"
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

//初期位置設定(引数：プレイヤー初期位置、ステージ番号)
//新しいステージを作ったときに呼ぶ
void RouteJudge::Init(int set_x, int set_y, state_stage stg) {
	//初期位置セット
	initialGrid.x = set_x;
	initialGrid.y = set_y;

	//ステージ番号セット
	stageNum = stg;

	//ステージの大きさをセット
	Width	= WIDTH;
	Height	= HEIGHT;

	Reset(set_x, set_y);
}

//リセット(引数はプレイヤー位置)
void RouteJudge::Reset(int set_x,int set_y)
{
	//マップデータを複製
	for (int i = 0; i < Height; i++) {
		memcpy(map[i], sMap[i], sizeof(sMap[i]));
	}

	//今の位置セット
	map[set_y][set_x] = Path;
	currentGrid.x = set_x;
	currentGrid.y = set_y;

	Perticleflg = false;
	isReset		= false;

	routeCount = 0;
	stageCount = 0;

	//パネル数のカウント
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			int tmp = map[i][j];
			if (tmp == Empty || tmp == Pole) {
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

	//初期位置補正
	float dat_x = (float)initialGrid.x + 0.5f;
	float dat_y = (float)initialGrid.y + 0.5f;

	//現在の位置を更新
	currentGrid.x = (int)(-pos.x / GRID_SIZE+ dat_x);
	currentGrid.y = (int)(pos.z / GRID_SIZE+ dat_y);

	//プレイヤーの初期位置を通ったマスにする
	if (Perticleflg == false) {
		routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
		routeObject[currentGrid.y][currentGrid.x]->Perticle();
		Perticleflg = true;
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
			CSoundSource* SE = NewGO<CSoundSource>(0);
			SE->Init("Assets/sound/kira2.wav");
			SE->Play(false);
			isReset = true;
		}
		//すでに通ったマスに移動
		//または、邪魔パネル(仮)
		else if (mapTmp == Path || mapTmp == 3) {
			//ゲームオーバー処理
			g_gameScene->SetGameOver();
		}
		//まだ通ってない道
		else{
			map[currentGrid.y][currentGrid.x] = Path;
			//通ったマスを描画する
			routeObject[currentGrid.y][currentGrid.x]->SetActiveFlag(true);
			routeObject[currentGrid.y][currentGrid.x]->Perticle();
			routeCount++;
		}
	}
}