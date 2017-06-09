#include "stdafx.h"
#include "TestEnemy.h"
#include "scene/GameScene.h"


TestEnemy::TestEnemy()
{
	skinModelData.LoadModelData("Assets/modelData/enemy_00.X", &animation);
}


TestEnemy::~TestEnemy()
{
}

void TestEnemy::Move()
{
	CVector3 toPlayer;
	CVector3 direction;
	CMatrix wMatrix = skinModel.GetWorldMatrix();
	direction.x = wMatrix.m[2][0];
	direction.y = wMatrix.m[2][1];
	direction.z = wMatrix.m[2][2];
	direction.Normalize();

	moveFrameCount++;
	if (Estate == eState_Search) {
		if (moveFrameCount % 40 == 0) {
			rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(90.0f * dir));
			dir += 1.0f;
		}
		toPlayer.Subtract(g_gameScene->getPlayer()->GetPosition(), position);
		float length = toPlayer.Length();
		toPlayer.Normalize();
		float angle = toPlayer.Dot(direction);
		angle = acos(angle);
		if (fabsf(angle) < D3DXToRadian(45.0f) && length < 5.0f) {
			Estate = eState_Find;
		}
		move = CVector3::Zero;
	}
	else if (Estate == eState_Find) {
		//”­Œ©ó‘Ô
		toPlayer.Subtract(g_gameScene->getPlayer()->GetPosition(), position);
		float length = toPlayer.Length();
		toPlayer.y = 0.0f;
		toPlayer.Normalize();
		float angle = toPlayer.Dot(CVector3::AxisZ);
		angle = acos(angle);
		if (toPlayer.x <= 0.0f)
		{
			angle *= -1.0f;
		}
		move = toPlayer;
		toPlayer.Scale(0.2f);
		position.Add(toPlayer);
		rotation.SetRotation(CVector3::AxisY, angle);
		if (WalkAnimation == false) {
			animation.PlayAnimation(AnimationWalk);
			WalkAnimation = true;
		}
		//ƒvƒŒƒCƒ„[‚Æ‚Ì‹——£‚ª‹ß‚¯‚ê‚ÎUŒ‚
		if (length < 2.0f && animation.GetPlayAnimNo() == AnimationWalk) {
			animation.PlayAnimation(AnimationAttack);
		}
		//UŒ‚’†‚ÍˆÚ“®‚µ‚È‚¢
		if (animation.GetPlayAnimNo() == AnimationAttack) {
			move = CVector3::Zero;
			if (length >= 2.0f) {
				WalkAnimation = false;
			}
		}
	}
}