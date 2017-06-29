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

	bool GetBlockflg() {
		return Blockflg;
	}

	bool GetBlock2flg() {
		return Block2flg;
	}

	bool GetReturnflg() {
		return Returnflg;
	}

	void SetBlockflg(bool flg) {
		Blockflg = flg;
	}

	void SetBlock2flg(bool flg) {
		Block2flg = flg;
	}

	void SetReturnflg(bool flg) {
		Returnflg = flg;
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
	int GetCount() {
		return Count;
	}
	void SetCount(int val) {
		Count = val;
	}
	void SetResetEnd(bool flg) {
		ResetEnd = flg;
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
	bool Blockflg = false;
	bool Block2flg = false;
	bool Returnflg = false;

	int StageCount;		//stage1をクリアするために必要なマスの数
	int RouteCount;		//現在のstageで通ったマスの数
	int Count;
};

