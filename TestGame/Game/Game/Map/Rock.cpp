#include "stdafx.h"
#include "Rock.h"
#include "scene/GameScene.h"

Rock* rock[2] = { nullptr, nullptr };

Rock::Rock()
{
}


Rock::~Rock()
{
}

void Rock::Init(CVector3 position, CQuaternion rotation)
{
	//CSkinModel��������
	skinModelData.LoadModelData("Assets/modelData/Rock1.x", NULL);
	skinModel.Init(skinModelData.GetBody());

	//�f�t�H���g���C�g�ݒ�
	skinModel.SetLight(&g_gameScene->getLight());
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//���[���h�s����쐬
	skinModel.Update(position, rotation, { 1.0f,1.0f,1.0f });

	this->position = position;		//�ʒu���L�^
	this->rotation = rotation;		//��]���L�^
}

void Rock::Update()
{
	if ((g_gameScene == nullptr) || g_gameScene->isObjectDelete()) {
		skinModel.SetShadowCasterFlag(false);
		skinModel.SetShadowReceiverFlag(false);
		//�������폜
		DeleteGO(this);
		return;
	}

	//�ʏ펞�����������Ȃ�
	if (g_gameScene->isStep() != GameScene::step_nomal) { return; }

	if (g_gameScene->getJudge()->GetBlock2flg() == true) {
		Move();
	}

	if (rock[Rockidx]->position.z < 9.0f) {
		position.z = 9.0f;
		g_gameScene->getJudge()->SetBlock2flg(false);
		RockChenge = false;
		Deleteflg = true;
	}
	if (rock[Rockidx]->position.z > 23.0f) {
		position.z = 23.0f;
		g_gameScene->getJudge()->SetBlock2flg(false);
		RockChenge = false;
		Deleteflg = true;
	}

	if (Deleteflg == true) {
		DeleteGO(rock[0]);
		DeleteGO(rock[1]);
		rock[0] = nullptr;
		rock[1] = nullptr;
	}

	skinModel.Update(position, rotation, { 1.0f,1.0f,1.0f });
}

void Rock::Move()
{
	CVector3 toPlayer;
	float length = 0.0f;
	toPlayer.Subtract({ -16.0f,3.0f,16.0f }, position);
	length = toPlayer.Length();

	if (length < 2.5f) {
		RockHit = true;
		RockChenge = true;
	}

	timer += GameTime().GetFrameDeltaTime();

	if (RockChenge) {
		move = CVector3::Zero;
		if (timer > 2.0f) {
			if (position.z > 16.0f) {
				move = UpPos;
			}
			else if (position.z < 16.0f) {
				move = DownPos;
			}
		}
	}
	else {
		if (position.z > 16.0f) {
			move = DownPos;
		}
		else if (position.z < 16.0f) {
			move = UpPos;
		}
	}

	position.Add(move);
}

void Rock::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}