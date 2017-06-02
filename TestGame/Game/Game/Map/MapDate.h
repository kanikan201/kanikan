/*
	�}�b�v�f�[�^
*/

#pragma once

//��}�X�̒���(��)
#define GRID_SIZE 8.0f

class MapData {
	//�}�b�v�O
	static const int MAP_0_HEIGHT = 9;
	static const int MAP_0_WIDTH = 7;
	static int sMap_00[MAP_0_HEIGHT][MAP_0_WIDTH];
	//�}�b�v�P
	static const int MAP_1_HEIGHT = 9;
	static const int MAP_1_WIDTH = 7;
	static int sMap_01[MAP_1_HEIGHT][MAP_1_WIDTH];
	//�}�b�v�Q
	static const int MAP_2_HEIGHT = 10;
	static const int MAP_2_WIDTH = 10;
	static int sMap_02[MAP_2_HEIGHT][MAP_2_WIDTH];
public:
	//�}�b�v����
	void SetMapInfo(int mapTmp, int x, int y);
	//�}�b�v���̎擾
	int GetMapInfo(int x, int y);
	//�}�b�v�̍���
	int GetHeight();
	//�}�b�v�̕�
	int GetWidth();

	void GetMapCpy(void *value);

	enum mapObj {
		Empty,
		Wall,
		Pole,
		Trap1,	//�ז��p�l��(��)
		Trap2,	//���Z�b�g�p�l��(��)
		Trap3,	//���[�v�p�l��(��)
		Path,
	};
};
//namespace {
//	const int WIDTH = 7;
//	const int HEIGHT = 9;
//
//	//0�͒n�ʁA1�͕ǁA2�͒��A5�͂��łɒʂ����}�X�A6�̓S�[��
//	static int sMap[HEIGHT][WIDTH] = {
//		{ 1, 1, 1, 1, 1, 1, 1 },
//		{ 1, 0, 0, /*6*/0, 0, 0, 1 },
//		{ 1, 0, 2, 0, 1, 0, 1 },
//		{ 1, 0, 0, 0, 0, 0, 1 },
//		{ 1, 1, 2, 1, 1, 1, 1 },
//		{ 1, 0, 0, 1, 0, 0, 1 },
//		{ 1, 0, 0, 0, 0, 0, 1 },
//		{ 1, 1, 1, 0, 0, 4, 1 },
//		{ 1, 1, 1, 1, 1, 1, 1 },
//	};
//}
//
//enum mapObj {
//	Empty,	//�����Ȃ�
//	Wall,	//��
//	Pole,	//��
//	Trap1,	//�ז��p�l��(��)
//	Trap2,	//���Z�b�g�p�l��(��)
//	Trap3,	//���[�v�p�l��(��)
//	Path,	//�ʂ���
//	Gaul,	//�S�[��
//};