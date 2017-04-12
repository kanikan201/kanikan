#include "stdafx.h"
#include "ClearMarker.h"
#include "Camera.h"
#include "scene/GameScene.h"
#include "scene/SceneManager.h"


ClearMarker::ClearMarker()
{
}


ClearMarker::~ClearMarker()
{
	skinModel.SetShadowCasterFlag(false);
	skinModel.SetShadowReceiverFlag(false);
}

void ClearMarker::Init(CVector3 position, CQuaternion rotation)
{
	//CSkinModel��������
	skinModelData.LoadModelData("Assets/modelData/clearMarker.x", NULL);
	skinModel.Init(&skinModelData);

	//�f�t�H���g���C�g�ݒ�
	skinModel.SetLight(&g_gameScene->getLight());
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	//���[���h�s����쐬(��񂾂�)
	skinModel.Update(position, rotation, CVector3::One);

	this->position = position;		//�ʒu���L�^
	this->rotation = rotation;		//��]���L�^

}

void ClearMarker::Update()
{
	//�v���C���[�Ǝ��g�̋���
	float dist = g_gameScene->getPlayer()->Distance(position);
	if (!flag && (dist < 1.0f) && Pad(0).IsTrigger(enButtonA)) {
		flag = true;
		g_gameScene->setClear(true);
	}

	if ((sceneManager->GetScene() != SceneManager::stateGame) || g_gameScene->isObjectDelete()) {
		//�������폜
		DeleteGO(this);
		return;
	}
}

void ClearMarker::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameScene->getCamera()->GetViewMatrix(), g_gameScene->getCamera()->GetProjectionMatrix());
}