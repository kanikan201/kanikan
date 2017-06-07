/*
	マップデータ
*/

#pragma once

//一マスの長さ(仮)
#define GRID_SIZE 8.0f

class MapData {
	//マップ０
	static const int MAP_0_HEIGHT = 9;
	static const int MAP_0_WIDTH = 7;
	static int sMap_00[MAP_0_HEIGHT][MAP_0_WIDTH];
	//マップ１
	static const int MAP_1_HEIGHT = 9;
	static const int MAP_1_WIDTH = 7;
	static int sMap_01[MAP_1_HEIGHT][MAP_1_WIDTH];
	//マップ２
	static const int MAP_2_HEIGHT = 10;
	static const int MAP_2_WIDTH = 10;
	static int sMap_02[MAP_2_HEIGHT][MAP_2_WIDTH];
public:
	//マップ情報の取得
	int GetMapInfo(int x, int y);
	//マップの高さ
	int GetHeight();
	//マップの幅
	int GetWidth();
};

enum mapObj {
	Empty,	//何もない
	Wall,	//壁
	Pole,	//柱
	Trap1,	//邪魔パネル(仮)
	ResetTrap,	//リセットパネル(仮)
	WarpTrap,	//ワープパネル(仮)
	Path,	//通った
	Gaul,	//ゴール
};