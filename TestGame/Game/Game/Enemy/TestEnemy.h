//�e�X�g�p�̓G

#pragma once
#include "Enemy.h"

class TestEnemy : public Enemy
{
public:
	TestEnemy();
	~TestEnemy();
	void Move();

private:
	float		dir = 1.0f;
};

