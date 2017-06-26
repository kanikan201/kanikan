/*
	�}�b�v�f�[�^
*/

#pragma once

//��}�X�̒���
#define GRID_SIZE 8.0f

class MapData {
	//�}�b�v�O�i�X�e�[�W1�j
	static const int MAP_0_HEIGHT = 9;
	static const int MAP_0_WIDTH = 7;
	static int sMap_00[MAP_0_HEIGHT][MAP_0_WIDTH];

	//�}�b�v�P�i�X�e�[�W2�j
	static const int MAP_1_HEIGHT = 10;
	static const int MAP_1_WIDTH = 8;
	static int sMap_01[MAP_1_HEIGHT][MAP_1_WIDTH];

	//�}�b�v�Q�i�X�e�[�W3�j
	static const int MAP_2_HEIGHT = 10;
	static const int MAP_2_WIDTH = 10;
	static int sMap_02[MAP_2_HEIGHT][MAP_2_WIDTH];
public:
	//�}�b�v���̎擾
	int GetMapInfo(int x, int y);
	//�}�b�v�̍���
	int GetHeight();
	//�}�b�v�̕�
	int GetWidth();
};

//�X�e�[�W�ԍ�
enum state_stage {
	en_Stage1,		//�X�e�[�W1
	en_Stage2,		//�X�e�[�W2
	en_Stage3,		//�X�e�[�W3
	en_end,			//�Q�[���N���A�����p�̃_�~�[
};

//�}�b�v�I�u�W�F�N�g�̎��
enum mapObj {
	Empty,			//�����Ȃ�
	Wall,			//��
	Pole,			//��
	Trap1,			//�ז��p�l��(��)
	ResetTrap,		//���Z�b�g�p�l��(��)
	WarpTrap,		//���[�v�p�l��(��)
	Path,			//�ʂ���
	Gaul,			//�S�[��
	Dummy,			//�B���ʘH
	Block1			//�c�ɋ��ރu���b�N
};