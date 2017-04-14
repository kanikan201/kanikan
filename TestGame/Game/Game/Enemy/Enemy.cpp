#include "stdafx.h"
#include "Enemy.h"
#include "Player/Player.h"
#include "Camera.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"


Enemy::Enemy()
{
	CRandom rand;
	rand.Init((unsigned long)time(NULL));
	start = rand.GetRandDouble;
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

	//animation.PlayAnimation(AnimationStand);
}

void Enemy::Update()
{
	if ((g_gameScene == nullptr) || g_gameScene->isObjectDelete()) {
		//�������폜
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		DeleteGO(this);
		return;
	}

	//�v���C���[�Ǝ��g�̋���
	float dist = g_gameScene->getPlayer()->Distance(position);
	if (dist < 1.0f) {
		g_gameScene->getPlayer()->SetPosition({ 0.0f,0.0f,0.0f });
	}

	m_timer += GameTime().GetFrameDeltaTime();
	if (!isMoving && m_timer > start) {
		isMoving = true;
		m_timer = 0.0f;
	}

	move = characterController.GetMoveSpeed();

	//����
	Move();

	characterController.SetMoveSpeed(move);		//�ړ����x��ݒ�
	characterController.Execute(GameTime().GetFrameDeltaTime());	//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ̎󂯎��
	centralPos.Add(position, central);

	skinModel.Update(position, rotation, { 2.5f, 2.5f, 2.5f });
}

//����
void Enemy::Move()
{
	if (!isMoving) { return; }

	if (m_timer > 2.0f) {
		dir *= -1.0f;
		m_timer = 0.0f;
		rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(90.0f*dir));
	}
	move.x = dir*5.0f;
}

//�_���[�W���󂯂�
void Enemy::Damage()
{
}

void Enemy::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}