/*
	�}�b�v�f�[�^
*/

#pragma once

//��}�X�̒���(��)
#define GRID_SIZE 8.0f

namespace {
	const int WIDTH = 7;
	const int HEIGHT = 9;

	//0�͒n�ʁA1�͕ǁA2�͒��A5�͂��łɒʂ����}�X�A6�̓S�[��
	static int sMap[HEIGHT][WIDTH] = {
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, /*6*/0, 0, 0, 1 },
		{ 1, 0, 2, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 2, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 4, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
	};
}

enum mapObj {
	Empty,	//�����Ȃ�
	Wall,	//��
	Pole,	//��
	Trap1,	//�ז��p�l��(��)
	Trap2,	//���Z�b�g�p�l��(��)
	Trap3,	//���[�v�p�l��(��)
	Path,	//�ʂ���
	Gaul,	//�S�[��
};