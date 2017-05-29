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
	void Reset(int set_x, int set_y);	//���Z�b�g

	bool isDelete()
	{
		return isReset;
	}

	//���ׂĒʂ�����
	bool isPassed() {
		if (stageCount == routeCount) {
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

	grid prevGrid;		//�O�̃}�X
	grid currentGrid;	//���̃}�X
	int map[HEIGHT][WIDTH];	//�}�b�v�f�[�^�̕�����

	bool Perticleflg;			//�p�[�e�B�N���̃t���O
	bool isReset = false;

	int stageCount;		//stage1���N���A���邽�߂ɕK�v�ȃ}�X�̐�
	int routeCount;		//���݂�stage�Œʂ����}�X�̐�
};

