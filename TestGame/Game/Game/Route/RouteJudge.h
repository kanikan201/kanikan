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
		if (StageCount == RouteCount) {
			return true;
		}
		return false;
	}

	int GetinitialGrid_x() {
		return initialGrid.x;
	}

	int GetinitialGrid_y() {
		return initialGrid.y;
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

	int StageCount;		//stage1���N���A���邽�߂ɕK�v�ȃ}�X�̐�
	int RouteCount;		//���݂�stage�Œʂ����}�X�̐�
};

