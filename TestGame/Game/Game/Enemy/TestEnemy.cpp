#include "stdafx.h"
#include "TestEnemy.h"
#include "scene/GameScene.h"

TestEnemy* enemy;

TestEnemy::TestEnemy()
{
	skinModelData.LoadModelData("Assets/modelData/enemy_00.X", &animation);

	currentAnimSetNo = AnimationStand;

	////�e�p�̃e�N�X�`���p�X
	//darkTex.Load("Assets/modelData/Skeleton_D_dark.png");

	////���f���̃e�N�X�`����
	//sprintf(TexName, "Skeleton_D_light.png");
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
			//�����A�j���[�V����
			animation.PlayAnimation(AnimationWalk);
			currentAnimSetNo = AnimationWalk;
		}
		move = CVector3::Zero;
		break;
	case AnimationWalk:
		//�������
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
		//�v���C���[�Ƃ̋������߂���΍U��
		if (length < 2.5f) {
			animation.PlayAnimation(AnimationAttack);
			currentAnimSetNo = AnimationAttack;
		}
		break;
	case AnimationAttack:
		//�U�����͓����Ȃ�
		move = CVector3::Zero;
		timer += GameTime().GetFrameDeltaTime();
		if (timer > 2.5f) {
			currentAnimSetNo = Waiting;
			timer = 0.0f;
			animation.PlayAnimation(AnimationStand);
		}
		break;
	case Waiting:
		timer += GameTime().GetFrameDeltaTime();
		if (timer > 1.0f) {
			toPlayer.Subtract(g_gameScene->getPlayer()->GetPosition(), position);
			length = toPlayer.Length();
			if (length > 2.0f) {
				currentAnimSetNo = AnimationWalk;
				animation.PlayAnimation(AnimationWalk);
			}
			else {
				currentAnimSetNo = AnimationAttack;
				animation.PlayAnimation(AnimationAttack);
			}
			timer = 0.0f;
		}
		break;
	default:
		break;
	}
}