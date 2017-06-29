#include "stdafx.h"
#include "Block.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"

Block* block = nullptr;

Block::Block()
{
}


Block::~Block()
{
}

void Block::Init(CVector3 position, CQuaternion rotation)
{
	//CSkinModel��������
	skinModelData.LoadModelData("Assets/modelData/block.x", NULL);
	skinModel.Init(skinModelData.GetBody());

	//�f�t�H���g���C�g�ݒ�
	skinModel.SetLight(&g_gameScene->getLight());
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//���[���h�s����쐬
	skinModel.Update(position, rotation, { 1.7f,3.0f,1.7f });

	this->position = position;		//�ʒu���L�^
	this->rotation = rotation;		//��]���L�^
}

void Block::Update()
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

	//�u���b�N�̃}�X�ɗ����瓮����
	if (g_gameScene->getJudge()->GetBlockflg() == true) {
		timer += GameTime().GetFrameDeltaTime();
		Move();
	}

	if (position.y < 0.0f) {
		position.y = 0.0f;
	}

	if (position.y > 20.0f) {
		position.y = 20.0f;
		Upflg = false;
		g_gameScene->getJudge()->SetBlockflg(false);
	}

	skinModel.Update(position, rotation, { 1.7f,1.7f,1.7f });
}

void Block::Move()
{
	if (position.y <= 0.0f && Upflg == false && timer >= 2.0f) {
		move = UpPos;
		Upflg = true;
	}
	else {
		if (Upflg == false) {
			move = DownPos;
		}
		//�v���C���[�ƃu���b�N�̋��������ɂȂ�����q�b�g
		float Blocklength = g_gameScene->getPlayer()->Distance(position);
		if (Blocklength < 5.0f) {
			PlayerHit = true;
		}
		/*else {
			PlayerHit = false;
		}*/
	}
	position.Add(move);
}

void Block::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}