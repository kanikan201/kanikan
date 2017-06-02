/*
	ルート判定クラス
*/

#pragma once
#include "Map/MapDate.h"

class RouteJudge :public IGameObject
{
public:
	RouteJudge();
	~RouteJudge();
	bool Start();
	void Update();
	void Init(int set_x, int set_y, state_stage stg);

	bool isDelete()
	{
		return isReset;
	}

	//すべて通ったか
	bool isPassed() {
		if (stageCount == routeCount) {
			return true;
		}
		return false;
	}
private:
	void Reset(int set_x, int set_y);	//リセット

	struct grid
	{
		int x;
		int y;
	};

	grid prevGrid;		//前のマス
	grid currentGrid;	//今のマス
	grid initialGrid;

	int map[20][20];		//マップデータの複製先(とりあえずおっきいサイズに)

	bool Perticleflg;		//パーティクルのフラグ
	bool isReset = false;

	int stageCount;			//stage1をクリアするために必要なマスの数
	int routeCount;			//現在のstageで通ったマスの数

	state_stage stageNum;	//今のステージ番号

	int Width = 0;			//今のステージの横幅
	int Height = 0;			//今のステージの縦幅
};

