#include "stdafx.h"
#include "TestEnemy.h"
#include "scene/GameScene.h"

TestEnemy* enemy;

TestEnemy::TestEnemy()
{
	skinModelData.LoadModelData("Assets/modelData/enemy_00.X", &animation);

	currentAnimSetNo = AnimationStand;

	//影用のテクスチャパス
	darkTex.Load("Assets/modelData/Skeleton_D_dark.png");

	//モデルのテクスチャ名
	sprintf(TexName, "Skeleton_D.png");
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
	float length = 0.0f;
	float angle = 0.0f;
	switch (currentAnimSetNo)
	{
	case AnimationStand:
		if (moveFrameCount % 40 == 0) {
			rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(90.0f * dir));
			dir += 1.0f;
		}
		toPlayer.Subtract(g_gameScene->getPlayer()->GetPosition(), position);
		length = toPlayer.Length();
		toPlayer.Normalize();
		angle = toPlayer.Dot(direction);
		angle = acos(angle);
		if (fabsf(angle) < D3DXToRadian(45.0f) && length < 5.0f) {
			//歩きアニメーション
			animation.PlayAnimation(AnimationWalk, 0.3f);
			currentAnimSetNo = AnimationWalk;
		}
		move = CVector3::Zero;
		break;
	case AnimationWalk:
		//発見状態
		toPlayer.Subtract(g_gameScene->getPlayer()->GetPosition(), position);
		length = toPlayer.Length();
		toPlayer.y = 0.0f;
		toPlayer.Normalize();
		angle = toPlayer.Dot(CVector3::AxisZ);
		angle = acos(angle);
		if (toPlayer.x <= 0.0f)
		{
			angle *= -1.0f;
		}
		move = toPlayer;
		toPlayer.Scale(0.8f);
		position.Add(toPlayer);
		rotation.SetRotation(CVector3::AxisY, angle);
		//プレイヤーとの距離が近ければ攻撃
		if (length < 2.5f) {
			animation.PlayAnimation(AnimationAttack, 0.3f);
			currentAnimSetNo = AnimationAttack;
		}
		break;
	case AnimationAttack:
		//攻撃中は動かない
		move = CVector3::Zero;
		timer += GameTime().GetFrameDeltaTime();
		if (timer > 2.5f) {
			currentAnimSetNo = Waiting;
			timer = 0.0f;
			animation.PlayAnimation(AnimationStand, 0.3f);
		}
		break;
	case Waiting:
		timer += GameTime().GetFrameDeltaTime();
		if (timer > 1.0f) {
			toPlayer.Subtract(g_gameScene->getPlayer()->GetPosition(), position);
			length = toPlayer.Length();
			if (length > 2.0f) {
				currentAnimSetNo = AnimationWalk;
				animation.PlayAnimation(AnimationWalk, 0.3f);
			}
			else {
				currentAnimSetNo = AnimationAttack;
				animation.PlayAnimation(AnimationAttack, 0.3f);
			}
			timer = 0.0f;
		}
		break;
	default:
		break;
	}
}