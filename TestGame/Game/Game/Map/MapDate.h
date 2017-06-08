/*
	�}�b�v�f�[�^
*/

#pragma once

//��}�X�̒���(��)
#define GRID_SIZE 8.0f

//�X�e�[�W�ԍ�
enum state_stage {
	en_Stage1,	//�X�e�[�W1
	en_Stage2,	//�X�e�[�W2
	en_Stage3,	//�X�e�[�W3
	en_end,		//�Q�[���N���A�����p�̃_�~�[
};

//�}�b�v�̃I�u�W�F�N�g
enum mapObj {
	Empty,	//�����Ȃ�
	Wall,	//��
	Pole,	//��
	Trap1,	//�ז��p�l��(��)
	ResetTrap,	//���Z�b�g�p�l��
	WarpTrap,	//���[�v�p�l��
	Path,	//�ʂ���
	Gaul,	//�S�[��
};

namespace {
	const int WIDTH = 7;
	const int HEIGHT = 9;

	//0�͒n�ʁA1�͕ǁA2�͒��A5�͂��łɒʂ����}�X�A6�̓S�[��
	static int sMap[HEIGHT][WIDTH] = {
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 2, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 2, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 4, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
	};
}