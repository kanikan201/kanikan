#include "stdafx.h"
#include "RouteObject.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"

RouteObject* routeObject[20][20];

RouteObject::RouteObject()
{
	SetActiveFlag(false);
}


RouteObject::~RouteObject()
{
	DeleteGO(perticle);
}

void RouteObject::Init(CVector3 position, CQuaternion rotation)
{
	//CSkinModel��������
	skinModelData.LoadModelData("Assets/modelData/route.x", NULL);
	skinModel.Init(skinModelData.GetBody());

	//�f�t�H���g���C�g�ݒ�
	if (g_gameScene->GetStage() == en_Stage1) {
		ambientLight = { 0.0f, 0.30f , 0.42f };
	}
	else if (g_gameScene->GetStage() == en_Stage2) {
		ambientLight = { 0.40f, 0.0f , 0.10f };
	}
	else {
		ambientLight = { 0.01f, 0.35f , 0.0f };
	}
	ambientLight.Scale(2.8f);
	light.SetAmbinetLight(ambientLight);
	skinModel.SetLight(&light);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	rotation.SetRotation(CVector3::AxisX, CMath::DegToRad(90.0f));
	//���[���h�s����쐬(��񂾂�)
	skinModel.Update(position, rotation, CVector3::One);

	this->position = position;		//�ʒu���L�^
	this->rotation = rotation;		//��]���L�^
}

void RouteObject::Update()
{
	if ((g_gameScene == nullptr) || g_gameScene->isObjectDelete()) {
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		//�������폜
		DeleteGO(this);
		return;
	}

	//�Â��Ȃ�
	if (!flag && g_gameScene->isStep() == GameScene::step_WaitGameOver) {
		GameOvered();
	}

	//���[�g�����Z�b�g
	if (g_gameScene->getJudge()->isDelete()) {
		SetActiveFlag(false);

		LightReset();

		DeleteGO(perticle);
	}
}

void RouteObject::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}

void RouteObject::Perticle()
{
	//return;

	perticle = NewGO<CParticleEmitter>(0);

	perticle->Init(g_random, g_gameScene->getCamera()->GetCamera(),
	{
		"Assets/sprite/Light.png",			//!<�e�N�X�`���̃t�@�C���p�X�B
		{ 0.0f,0.0f,0.0f },					//!<�����x�B
		0.3f,								//!<�����B�P�ʂ͕b�B
		0.03f,								//!<�������ԁB�P�ʂ͕b�B
		3.0f,								//!<�p�[�e�B�N���̕��B
		3.0f,								//!<�p�[�e�B�N���̍����B
		{ 3.0f,1.5f,3.0f },					//!<�����ʒu�̃����_�����B
		{ 0.0f,0.0f,0.0f },					//!<�����x�̃����_�����B
		{ 0.0f,0.0f,0.0f },					//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		{
			{ 0.0f,0.0f,1.0f,1.0f },			//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			{ 0.0f,0.0f,0.0f,0.0f },
			{ 0.0f,0.0f,0.0f,0.0f },
			{ 0.0f,0.0f,0.0f,0.0f }
		},
		1,									//!<UV�e�[�u���̃T�C�Y�B
		{ 0.0f,-2.0f,0.0f },					//!<�d�́B
		true,								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		0.3f,								//!<�t�F�[�h���鎞�ԁB
		1.0f,								//!<�����A���t�@�l�B
		true,								//!<�r���{�[�h�H
		0.0f,								//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		1,									//!<0�����������A1���Z�����B
		{ 1.0f,1.0f,1.0f },					//!<��Z�J���[�B
	},
		position);							//�p�[�e�B�N���̈ʒu
}

void RouteObject::GameOvered() {
	//�Â����C�g(��)
	//�f�t�H���g���C�g�ݒ�
	if (g_gameScene->GetStage() == en_Stage1) {
		ambientLight = { 0.0f, 0.20f , 0.20f };
	}
	else if (g_gameScene->GetStage() == en_Stage2) {
		ambientLight = { 0.20f, 0.0f , 0.10f };
	}
	else {
		ambientLight = { 0.03f, 0.20f , 0.0f };
	}
	ambientLight.Scale(2.8f);
	light.SetAmbinetLight(ambientLight);
	skinModel.SetLight(&light);
}

void RouteObject::LightReset()
{
	light.SetAmbinetLight(ambientLight);
	skinModel.SetLight(&light);
	flag = false;
}

void RouteObject::SetWorp()
{
	SetActiveFlag(true);
	//���[�v�̐F(��)
	CVector3 aLight = { 0.30f, 0.30f , 0.00f };
	aLight.Scale(2.8f);
	light.SetAmbinetLight(aLight);
	skinModel.SetLight(&light);
	flag = true;
}

void RouteObject::SetResetLight() {
	SetActiveFlag(true);
	//���Z�b�g�̐F(��)
	CVector3 aLight = { 0.30f, 0.30f , 0.30f };
	aLight.Scale(2.8f);
	light.SetAmbinetLight(aLight);
	skinModel.SetLight(&light);
	flag = true;
}

void RouteObject::SetTrap() {
	SetActiveFlag(true);
	//�ז��p�l���̐F(��)
	CVector3 aLight = { 0.01f, 0.01f , 0.01f };
	aLight.Scale(2.8f);
	light.SetAmbinetLight(aLight);
	skinModel.SetLight(&light);
	flag = true;
}