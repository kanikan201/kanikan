/*
	マップデータ
*/

#pragma once

//一マスの長さ(仮)
#define GRID_SIZE 8.0f

//ステージ番号
enum state_stage {
	en_Stage1,	//ステージ1
	en_Stage2,	//ステージ2
	en_Stage3,	//ステージ3
	en_end,		//ゲームクリア処理用のダミー
};

//マップのオブジェクト
enum mapObj {
	Empty,	//何もない
	Wall,	//壁
	Pole,	//柱
	Trap1,	//邪魔パネル(仮)
	ResetTrap,	//リセットパネル
	WarpTrap,	//ワープパネル
	Path,	//通った
	Gaul,	//ゴール
};

namespace {
	const int WIDTH = 7;
	const int HEIGHT = 9;

	//0は地面、1は壁、2は柱、5はすでに通ったマス、6はゴール
	static int sMap[HEIGHT][WIDTH] = {
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 2, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 2, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 4, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
	};
}