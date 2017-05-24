/*
	マップデータ
*/

#pragma once

//一マスの長さ(仮)
#define GRID_SIZE 8.0f

namespace {
	const int WIDTH = 7;
	const int HEIGHT = 9;

	//0は地面、1は壁、2は柱、5はすでに通ったマス、6はゴール
	static int sMap[HEIGHT][WIDTH] = {
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, /*6*/0, 0, 0, 1 },
		{ 1, 0, 2, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 2, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 4, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
	};
}

enum mapObj {
	Empty,	//何もない
	Wall,	//壁
	Pole,	//柱
	Trap1,	//邪魔パネル(仮)
	Trap2,	//リセットパネル(仮)
	Trap3,	//ワープパネル(仮)
	Path,	//通った
	Gaul,	//ゴール
};