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
	void Init(int set_x, int set_y);

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
	grid initialGrid;

	int map[20][20];	//�}�b�v�f�[�^�̕�����(�Ƃ肠�������������T�C�Y��)

	bool Perticleflg;			//�p�[�e�B�N���̃t���O
	bool isReset = false;

	int stageCount;		//stage1���N���A���邽�߂ɕK�v�ȃ}�X�̐�
	int routeCount;		//���݂�stage�Œʂ����}�X�̐�
};

