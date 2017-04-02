#include "stdafx.h"
#include "Enemy.h"
#include "Player/Player.h"
#include "Camera.h"
#include "scene/GameScene.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	characterController.RemoveRigidBoby();
}

void Enemy::Init(CVector3 pos)
{
	skinModelData.LoadModelData("Assets/modelData/D_Unity.X", &animation);

	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_gameScene->getLight());			//�f�t�H���g���C�g��ݒ�B
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	position = pos;
	centralPos.Add(position, central);

	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(90.0f));

	characterController.Init(0.5f, 1.0f, position);	//�L�����N�^�R���g���[���̏������B

	//animation.SetAnimationEndTime(AnimationRun, 0.8);
	//animation.PlayAnimation(AnimationStand);
}

void Enemy::Update()
{
	/*
	//HP��0�ɂȂ���
	if (scene->isDelete() || state.hp <= 0) {
		g_player->SetScore(state.score);
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
	}

	length = g_player->Distance(centralPos);
	if (!workFlag) {
		if (length > Limit) { return; }
		workFlag = true;
	}

	//�v���C���[�ƐڐG
	if (length <= 3.0f) {
		g_player->Damage(centralPos);
	}

	this->Damage();
	*/

	move = characterController.GetMoveSpeed();

	//����
	Move();

	characterController.SetMoveSpeed(move);		//�ړ����x��ݒ�
	characterController.Execute(GameTime().GetFrameDeltaTime());					//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ̎󂯎��
	centralPos.Add(position, central);

	skinModel.Update(position, rotation, CVector3::One);
}

//����
void Enemy::Move()
{

}

//�_���[�W���󂯂�
void Enemy::Damage()
{
}

void Enemy::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}