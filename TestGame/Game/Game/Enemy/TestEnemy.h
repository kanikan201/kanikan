//テスト用の敵

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

