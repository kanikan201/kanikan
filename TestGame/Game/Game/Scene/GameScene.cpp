#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "fade/Fade.h"

GameScene* g_gameScene = NULL;

//�}�b�v�̔z�u���
SMapInfo Stage[] = {
#include "locationInfo.h"
};

GameScene::GameScene()
{
	
}
GameScene::~GameScene()
{

}

bool GameScene::Start()
{
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

	map		= NewGO<Map>(0);		//�}�b�v����
	int numObject;
	//�}�b�v�ɔz�u����Ă���I�u�W�F�N�g�����v�Z
	numObject = sizeof(Stage) / sizeof(Stage[0]);
	map->Create(Stage, numObject);
	player	= NewGO<Player>(0);		//�v���C���[����
	camera	= NewGO<Camera>(0);		//�J��������
	ivt = NewGO<inventory>(0);

	g_fade->StartFadeIn();
	return true;
}

void GameScene::Update()
{

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