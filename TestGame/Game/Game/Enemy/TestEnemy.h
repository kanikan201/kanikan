//テスト用の敵

#pragma once
#include "Enemy.h"

class TestEnemy : public Enemy
{
public:
	TestEnemy();
	~TestEnemy();
	CVector3 GetPosition() {
		return position;
	}
private:
	void Move()override;
	CMatrix*    matrix;
	float		dir = 1.0f;
	float		timer = 0.0f;			//タイマー
	int			moveFrameCount = 0;
};

extern TestEnemy* enemy;