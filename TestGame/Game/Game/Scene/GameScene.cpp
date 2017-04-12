#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "fade/Fade.h"

GameScene* g_gameScene = NULL;

//�}�b�v�̔z�u���
SMapInfo Stage1[] = {
#include "locationInfo.h"
};
//�}�b�v�̔z�u���
SMapInfo Stage2[] = {
#include "locationInfo2.h"
};

GameScene::GameScene()
{
	
}
GameScene::~GameScene()
{

}

bool GameScene::Start()
{
	if (fadeStep == step_WaitFadeOut) {
		//���C�g��������
		light.SetDiffuseLightDirection(0, { 0.707f, 0.0f, -0.707f });
		light.SetDiffuseLightDirection(1, { -0.707f, 0.0f, -0.707f });
		light.SetDiffuseLightDirection(2, { 0.0f, 0.707f, -0.707f });
		light.SetDiffuseLightDirection(3, { 0.0f, -0.707f, -0.707f });

		light.SetDiffuseLightColor(0, { 0.2f, 0.2f, 0.2f, 1.0f });
		light.SetDiffuseLightColor(1, { 0.2f, 0.2f, 0.2f, 1.0f });
		light.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
		light.SetDiffuseLightColor(3, { 0.2f, 0.2f, 0.2f, 1.0f });
		light.SetAmbinetLight({ 0.3f, 0.3f, 0.3f });

		//light.SetLimLightColor(CVector4(0.6f, 0.6f, 0.6f, 1.0f));
		//light.SetLimLightDirection(CVector3(0.0f, 0.0f, -1.0f));

		map = NewGO<Map>(0);		//�}�b�v����
		int numObject;
		//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
		numObject = sizeof(Stage1) / sizeof(Stage1[0]);
		map->Create(Stage1, numObject);

		player = NewGO<Player>(0);		//�v���C���[����
		camera = NewGO<Camera>(0);		//�J��������
		ivt = NewGO<inventory>(0);

		fadeStep = step_StageLoad;
		return false;
	}
	else {
		fadeStep = step_WaitFadeIn;
		g_fade->StartFadeIn();
	}
	return true;
}

void GameScene::Update()
{

	switch (fadeStep) {

		//�X�e�[�W�̓ǂݍ��݂��I�����
	case step_StageLoad:
		g_fade->StartFadeIn();
		fadeStep = step_WaitFadeIn;
		break;

	//�t�F�[�h�A�E�g��
	case step_WaitFadeIn:
		//�t�F�[�h���I�����
		if (!g_fade->IsExecute()) {
			fadeStep = step_nomal;
		}
		break;

	//�ʏ펞
	case step_nomal:
		//�N���A����
		if (isClear == true) {
			g_fade->StartFadeOut();
			fadeStep = step_WaitFadeOut;
		}
		break;
	//�t�F�[�h�A�E�g��
	case step_WaitFadeOut:
		//�I�u�W�F�N�g���폜����
		if (isDelete == true) {
			isDelete = false;
			ChangeStage();
			fadeStep = step_StageLoad;
		}
		//�t�F�[�h���I�����
		else if (!g_fade->IsExecute()) {
			player->SetPosition({ 0.0f, 0.0f, 0.0f });
			setClear(false);
			//�I�u�W�F�N�g���폜
			isDelete = true;
		}
		break;
	}
}

void GameScene::ChangeStage()
{
	int numObject;
	switch (currentStage) {
	case en_Stage1:
		//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
		numObject = sizeof(Stage2) / sizeof(Stage2[0]);
		map->Create(Stage2, numObject);
		currentStage = en_Stage2;
		break;
	case en_Stage2:
		//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
		numObject = sizeof(Stage2) / sizeof(Stage2[0]);
		map->Create(Stage2, numObject);
		currentStage = en_Stage2;
		break;
	}
}
/*!
*@brief	�`��֐��B
*/
void GameScene::Render(CRenderContext& renderContext)
{

}

//�����������̂��������
void GameScene::Release() {
	DeleteGO(camera);	//�J����
	DeleteGO(player);	//�v���C���[
	DeleteGO(map);		//�}�b�v
	DeleteGO(ivt);
}