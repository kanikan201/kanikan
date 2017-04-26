#pragma once

//一マスの長さ?
#define GRID_SIZE 3.0f

namespace {
	const int WIDTH = 7;
	const int HEIGHT = 9;

	//0は地面、1は壁、2は柱、5はすでに通ったマス
	static int sMap[HEIGHT][WIDTH] = {
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 2, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 2, 1, 2, 1, 1 },
		{ 1, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
	};
}