//�e�X�g�p�̓G

#pragma once
#include "Enemy.h"

class TestEnemy : public Enemy
{
public:
	TestEnemy();
	~TestEnemy();

private:
	void Move()override;
	float		dir = 1.0f;
	int moveFrameCount = 0;
};

