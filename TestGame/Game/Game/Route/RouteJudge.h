/*
	���[�g����N���X
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
	void Reset(int set_x, int set_y);	//���Z�b�g
	void Warp();

	//���[�g�I�u�W�F�N�g�����Z�b�g���邩
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
private:
	

	struct grid
	{
		int x;
		int y;
	};

	grid prevGrid;		//�O�̃}�X
	grid currentGrid;	//���̃}�X
	grid initialGrid;	//�����}�X
	grid warpGrid[2];	//���[�v�O���b�h


	int map[20][20];	//�}�b�v�f�[�^�̕�����(�Ƃ肠�����傫���T�C�Y��)

	bool InitroutePos;			
	bool isReset = false;
	bool Perticleflg = false;	//�p�[�e�B�N���̃t���O

	int StageCount;		//stage1���N���A���邽�߂ɕK�v�ȃ}�X�̐�
	int RouteCount;		//���݂�stage�Œʂ����}�X�̐�
};

