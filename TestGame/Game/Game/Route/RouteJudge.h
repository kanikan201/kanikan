/*
	ルート判定クラス
*/


#pragma once
#include "Map/MapData.h"

class RouteJudge :public IGameObject
{
public:
	RouteJudge();
	~RouteJudge();
	bool Start();
	void Update();
	void Init(int set_x, int set_y);

	//ルートオブジェクトをリセットするか
	bool isDelete()
	{
		return isReset;
	}

	//すべて通ったか
	bool isPassed() {
		if (StageCount == RouteCount) {
			return true;
		}
		return false;
	}

	int GetInitialGrid_x() {
		return initialGrid.x;
	}

	int GetInitialGrid_y() {
		return initialGrid.y;
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

	int map[20][20];	//マップデータの複製先(とりあえず大きいサイズに)

	bool InitroutePos;			//パーティクルのフラグ
	bool isReset = false;

	int StageCount;		//stage1をクリアするために必要なマスの数
	int RouteCount;		//現在のstageで通ったマスの数
};

