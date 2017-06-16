//テスト用の敵

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
	float		timer = 0.0f;			//タイマー
	int			moveFrameCount = 0;
};

