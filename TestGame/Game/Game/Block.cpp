#include "stdafx.h"
#include "Block.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"
#include "Route\RouteJudge.h"

Block* block;

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

	characterController.Init(5.0f, 5.0f, position);	//�L�����N�^�R���g���[���̏������B
	characterController.SetMoveSpeed(move);

	//���[���h�s����쐬
	skinModel.Update(position, rotation, { 1.7f,1.7f,1.7f });

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

	if (g_gameScene->getJudge()->GetBlockflg() == true) {
		Move();
	}

	if (position.y > 20.0f) {
		position.y = 20.0f;
		Upflg = false;
	}

	skinModel.Update(position, rotation, { 1.7f,1.7f,1.7f });
}

void Block::Move()
{
	
	if (position.y <= 2.0f && Upflg == false) {
		move = UpPos;
		Upflg = true;
	}
	else {
		if (Upflg == false) {
			move = DownPos;
		}
	}
	characterController.SetMoveSpeed(move);		//�ړ����x��ݒ�
	characterController.Execute(GameTime().GetFrameDeltaTime());	//�L�����N�^�[�R���g���[�����s
	position = characterController.GetPosition();	//���s���ʂ̎󂯎��
}

void Block::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}