/*
	���[�g����N���X
*/


#pragma once
#include "Map\MapDate.h"

class RouteJudge :public IGameObject
{
public:
	RouteJudge();
	~RouteJudge();
	bool Start();
	void Update();
	void Reset(int set_x, int set_y);
	bool isDelete()
	{
		return isReset;
	}
	bool isPassed() {
		if (stageCount == routeCount) {
			//�Q�[���N���A����
			return true;
		}
		return false;
	}
private:
	struct grid
	{
		int x;
		int y;
	};

	grid prevGrid;
	grid currentGrid;
	int map[HEIGHT][WIDTH];
	bool Perticleflg;			//�p�[�e�B�N���̃t���O
	bool isReset=false;

	int stageCount;		//stage1���N���A���邽�߂ɕK�v�ȃ}�X�̐�
	int routeCount;			//���݂�stage�Œʂ����}�X�̐�
};

