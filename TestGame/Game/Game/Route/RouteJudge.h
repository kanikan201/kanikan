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
	void Reset(int set_x, int set_y);	//リセット
	void Warp();
	void Change();

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

	int GetCurrentGrid_x() {
		return currentGrid.x;
	}

	int GetCurrentGrid_y() {
		return currentGrid.y;
	}
private:
	

	struct grid
	{
		int x;
		int y;
	};

	grid prevGrid;		//前のマス
	grid currentGrid;	//今のマス
	grid initialGrid;	//初期マス
	grid warpGrid[2];	//ワープグリッド

	int CountPlus = 0;
	int map[20][20];	//マップデータの複製先(とりあえず大きいサイズに)

	bool InitroutePos;
	bool isChange = false;
	bool isReset = false;
	bool ResetEnd = false;
	bool Perticleflg = false;	//パーティクルのフラグ

	int StageCount;		//stage1をクリアするために必要なマスの数
	int RouteCount;		//現在のstageで通ったマスの数
};

