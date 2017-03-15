#include "stdafx.h"
#include "Player.h"
#include "scene/GameScene.h"

Player::Player()
{
}

Player::~Player()
{
	characterController.RemoveRigidBoby();
}

bool Player::Start() {
	skinModelData.LoadModelData("Assets/modelData/Unity.X", &animation);

	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_gameScene->getLight());			//�f�t�H���g���C�g��ݒ�B
	characterController.Init(0.5f, 1.0f, position);	//�L�����N�^�R���g���[���̏������B

	animation.SetAnimationEndTime(AnimationRun, 0.8);
	animation.PlayAnimation(AnimationStand);

	return true;
}

void Player::Update()
{
	anim = currentAnimSetNo;

	//�L�����N�^�[�̈ړ����x
	CVector3 move = characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * 5.0f;
	move.z = -Pad(0).GetLStickYF() * 5.0f;

	//A�{�^���ŃW�����v
	if (Pad(0).IsTrigger(enButtonA) && !characterController.IsJump()) {
		move.y = 8.0f;
		characterController.Jump();
	}

	characterController.SetMoveSpeed(move);	//�ړ����x��ݒ�
	characterController.Execute(GameTime().GetFrameDeltaTime());			//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ̎󂯎��

//�����Ă�Ƃ�
	if (move.x != 0.0f || move.z != 0.0f) 
	{
		currentAnimSetNo = AnimationRun;
		dir.x = -Pad(0).GetLStickXF();
		dir.z = -Pad(0).GetLStickYF();

		//�����ύX
		rotation.SetRotation(CVector3::AxisY, atan2f(dir.x, dir.z));
	}
//�����Ă�Ƃ�
	else 
	{
		currentAnimSetNo = AnimationStand;
	}

//���[�V�������ς���Ă���ύX����
	if (currentAnimSetNo != anim) {
		animation.PlayAnimation(currentAnimSetNo,0.3f);
	}

	//�A�j���[�V�����X�V
	animation.Update(1.0f / 30.0f);
	skinModel.Update(position, rotation, {2.5f, 2.5f, 2.5f});
}

void Player::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}


//�v���C���[�ƑΏۂ̋������v�Z���ĕԂ�
float Player::Distance(CVector3& objectPos)
{
	CVector3 diff;

	//�v���C���[�̍��W����G�̍��W�����Z
	diff.Subtract(position, objectPos);
	//�G�ƃv���C���[�̋������v�Z
	return diff.Length();
}