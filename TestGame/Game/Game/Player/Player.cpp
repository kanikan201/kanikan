#include "stdafx.h"
#include "Player.h"
#include "scene/GameScene.h"

#define SPEED 7.0f

Player::Player()
{
}

Player::~Player()
{
	skinModel.SetShadowCasterFlag(false);
	skinModel.SetShadowReceiverFlag(false);
	characterController.RemoveRigidBoby();
}

bool Player::Start() {
	skinModelData.LoadModelData("Assets/modelData/Unity.X", &animation);

	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&g_gameScene->getLight());			//�f�t�H���g���C�g��ݒ�B

	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(180.0f));

	CVector3 lightPos = CVector3(0.0f, 20.5f, 24.5f);
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(position);
	toLightPos.Subtract(lightPos, position);

	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);
	characterController.Init(0.5f, 1.0f, position);	//�L�����N�^�R���g���[���̏������B

	animation.SetAnimationEndTime(AnimationRun, 0.8);
	animation.PlayAnimation(AnimationStand);

	darkTex.Load("Assets/modelData/utc_all2_dark.png");
	std::vector<CSkinModelMaterial*> matList;
	skinModelData.GetBody()->FindMaterials(matList, "utc_all2_light.png");
	//���X�g���󂶂�Ȃ�
	if (!matList.empty()) {
		for (size_t i = 0; i < matList.size(); i++)
		{
			if (matList[i]->GetTechnique() == CSkinModelMaterial::enTecShaderHandle_SkinModel) {
				matList[i]->Build(CSkinModelMaterial::enTypeToon);
			}
			else {
				matList[i]->Build(CSkinModelMaterial::enTypeToonNonSkin);
			}
			matList[i]->SetTexture(CSkinModelMaterial::enTextureShaderHandle_DarkTex, darkTex);
		}
	}
	return true;
}

void Player::Update()
{
	//�؂�ւ�莞�͏������Ȃ�
	if (g_gameScene->isStep() != GameScene::step_nomal) { return; }

	//�O�̃A�j���[�V������ۑ�
	prevAnim = currentAnimSetNo;

	//�ړ�
	characterController.SetMoveSpeed(Move());	//�ړ����x��ݒ�
	characterController.Execute(GameTime().GetFrameDeltaTime());	//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ��󂯎��

//�ړ����Ă�
	if (!(g_gameScene->GetClear() || g_gameScene->getCamera()->GetChengeIn())
		&& (Pad(0).GetLStickXF()!=0.0f || Pad(0).GetLStickYF() != 0.0f))
	{
		//����A�j���[�V����
		currentAnimSetNo = AnimationRun;
		//������ύX
		rotation.SetRotation(CVector3::AxisY, atan2f(dir.x, dir.z));

		if (!characterController.IsJump()) {
			timer += GameTime().GetFrameDeltaTime();

			if (timer > 0.4f) {
				//����
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->Init("Assets/sound/footstep.wav");
				se->Play(false);
				timer = 0.0f;
			}
		}
	}
//�����Ă�Ƃ�
	else 
	{
		//�����A�j���[�V����
		currentAnimSetNo = AnimationStand;
	}

//���[�V�������ς���Ă���ύX����
	if (currentAnimSetNo != prevAnim) {
		animation.PlayAnimation(currentAnimSetNo,0.3f);
	}

	//�A�j���[�V�����X�V
	animation.Update(1.0f / 30.0f);
	skinModel.Update(position, rotation, {2.5f, 2.5f, 2.5f});

	//�e
	ShadowMap().SetLightTarget(position);
	CVector3 lightPos;
	lightPos.Add(position, toLightPos);
	ShadowMap().SetLightPosition(lightPos);
}

CVector3 Player::Move()
{

	//�L�����N�^�[�̈ړ����x�擾
	CVector3 move = characterController.GetMoveSpeed();
	if (g_gameScene->GetClear()|| g_gameScene->getCamera()->GetChengeIn()) {
		move.x = 0.0f;
		move.z = 0.0f;
		return move; 
	}

	//A�{�^���ŃW�����v
	if (Pad(0).IsTrigger(enButtonA) && !characterController.IsJump()) {
		move.y = 8.0f;
		characterController.Jump();
		CSoundSource* SE = NewGO<CSoundSource>(0);
		SE->Init("Assets/sound/V0001.wav");
		SE->Play(false);
	}

	//�L�����̐i�s�����̌v�Z
	CVector3 moveDirLocal;	//���͂��ꂽ����
	moveDirLocal.y = 0.0f;
	moveDirLocal.x = Pad(0).GetLStickXF();
	moveDirLocal.z = Pad(0).GetLStickYF();

	const CMatrix& mViewInv = g_gameScene->getCamera()->GetViewMatrixInv();

	//�J������Ԃ��猩���������̃x�N�g�����擾(Z)
	CVector3 cameraZ;
	cameraZ.x = mViewInv.m[2][0];
	cameraZ.y = 0.0f;		//Y���͂���Ȃ�
	cameraZ.z = mViewInv.m[2][2];
	cameraZ.Normalize();	//Y����ł������Ă���̂Ő��K������B

	//�J�������猩���������̃x�N�g�����擾(X)
	CVector3 cameraX;
	cameraX.x = mViewInv.m[0][0];
	cameraX.y = 0.0f;		//Y���͂���Ȃ�
	cameraX.z = mViewInv.m[0][2];
	cameraX.Normalize();	//Y����ł������Ă���̂Ő��K������B

	//�L�����̌����̌v�Z
	dir.x = cameraX.x * moveDirLocal.x + cameraZ.x * moveDirLocal.z;
	dir.y = 0.0f;	//Y�����͖���
	dir.z = cameraX.z * moveDirLocal.x + cameraZ.z * moveDirLocal.z;

	move.x = dir.x * SPEED;
	move.z = dir.z * SPEED;

	if (characterController.IsJump()) {
		move.x = move.x * 2 / 3;
		move.z = move.z * 2 / 3;
	}

	return move;
}

void Player::Render(CRenderContext& renderContext)
{
	//�g�D�[���V�F�[�_�ݒ�
	std::vector<CSkinModelMaterial*> matList;
	skinModelData.GetBody()->FindMaterials(matList, "utc_all2_light.png");
	//���X�g���󂶂�Ȃ�
	if (!matList.empty()) {
		for (size_t i = 0; i < matList.size(); i++)
		{
			matList[i]->SetTexture(CSkinModelMaterial::enTextureShaderHandle_DepthTex, *Dof().GetDepthRenderTarget()->GetTexture());
			matList[i]->SetInt(CSkinModelMaterial::enIntShaderHandle_IsZPrepass, CEngine::Instance().isZPrepass());
		}
	}

	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}

void Player::SetPosition(CVector3 pos) 
{
	characterController.SetPosition(pos);
	characterController.Execute(GameTime().GetFrameDeltaTime());	//�L�����N�^�[�R���g���[�����s
	position = pos;
	//�e
	ShadowMap().SetLightTarget(position);
	CVector3 lightPos;
	lightPos.Add(position, toLightPos);
	ShadowMap().SetLightPosition(lightPos);

	skinModel.Update(position, rotation, { 2.5f, 2.5f, 2.5f });
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

void Player::Reset()
{
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(180.0f));
	SetPosition({ 0.0f,0.0f,0.0f });
}