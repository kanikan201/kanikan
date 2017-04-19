#include "stdafx.h"
#include "TestEnemy.h"


TestEnemy::TestEnemy()
{
	skinModelData.LoadModelData("Assets/modelData/D_Unity.X", &animation);
}


TestEnemy::~TestEnemy()
{
}

void TestEnemy::Move()
{
	if (!isMoving) { return; }

	if (m_timer > 2.0f) {
		dir *= -1.0f;
		m_timer = 0.0f;
		rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(90.0f*dir));
	}
	move.x = dir*5.0f;
}