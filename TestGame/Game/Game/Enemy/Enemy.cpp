#include "stdafx.h"
#include "Enemy.h"
#include "Player/Player.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"


Enemy::Enemy()
{
	CRandom rand;
	rand.Init((unsigned long)time(NULL));
	start = rand.GetRandInt() % 15;
	start /= 10.0f;
	move = CVector3::Zero;
}


Enemy::~Enemy()
{
	characterController.RemoveRigidBoby();
}

void Enemy::Init(CVector3 pos)
{
	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&g_gameScene->getLight());			//�f�t�H���g���C�g��ݒ�B
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	////�g�D�[���ݒ�
	//std::vector<CSkinModelMaterial*> matList;
	//skinModelData.GetBody()->FindMaterials(matList, TexName);
	////���X�g���󂶂�Ȃ�
	//if (!matList.empty()) {
	//	for (size_t i = 0; i < matList.size(); i++)
	//	{
	//		if (matList[i]->GetTechnique() == CSkinModelMaterial::enTecShaderHandle_SkinModel) {
	//			matList[i]->Build(CSkinModelMaterial::enTypeToon);
	//		}
	//		else {
	//			matList[i]->Build(CSkinModelMaterial::enTypeToonNonSkin);
	//		}
	//		matList[i]->SetTexture(CSkinModelMaterial::enTextureShaderHandle_DarkTex, darkTex);
	//	}
	//}

	position = pos;
	centralPos.Add(position, central);

	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(90.0f));

	characterController.Init(0.5f, 1.0f, position);	//�L�����N�^�R���g���[���̏������B
	characterController.SetMoveSpeed(move);

	animation.PlayAnimation(AnimationStand);
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

	//�ʏ펞�����������Ȃ�
	if (g_gameScene->isStep() != GameScene::step_nomal) { return; }

	//�v���C���[�Ǝ��g�̋���
	float dist = g_gameScene->getPlayer()->Distance(position);
	if (dist < 2.0f) {
		g_gameScene->getPlayer()->DownAnimation();
		g_gameScene->SetGameOver();
	}

	m_timer += GameTime().GetFrameDeltaTime();
	if (!isMoving && m_timer > start) {
		isMoving = true;
		m_timer = 0.0f;
	}

	move = characterController.GetMoveSpeed();

	if (g_gameScene->GetClear() || g_gameScene->getCamera()->GetChengeIn()) {
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else {
		//����
		Move();
	}

	characterController.SetMoveSpeed(move);		//�ړ����x��ݒ�
	characterController.Execute(GameTime().GetFrameDeltaTime());	//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ̎󂯎��
	centralPos.Add(position, central);

	animation.Update(GameTime().GetFrameDeltaTime());
	skinModel.Update(position, rotation, { 1.5f, 1.5f, 1.5f });
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
	////�g�D�[���V�F�[�_�ݒ�
	//std::vector<CSkinModelMaterial*> matList;
	//skinModelData.GetBody()->FindMaterials(matList, TexName);
	////���X�g���󂶂�Ȃ�
	//if (!matList.empty()) {
	//	for (size_t i = 0; i < matList.size(); i++)
	//	{
	//		matList[i]->SetTexture(CSkinModelMaterial::enTextureShaderHandle_DepthTex, *Dof().GetDepthRenderTarget()->GetTexture());
	//		matList[i]->SetInt(CSkinModelMaterial::enIntShaderHandle_IsZPrepass, CEngine::Instance().isZPrepass());
	//	}
	//}
	//skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}