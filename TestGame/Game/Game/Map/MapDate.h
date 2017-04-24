#pragma once

#define GRID_SIZE 3.0f

namespace {
	const int WIDTH = 7;
	const int HEIGHT = 9;

	//0�͒n�ʁA1�͕ǁA2�͒��A5�͂��łɒʂ����}�X
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